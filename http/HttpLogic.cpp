/*
 * =====================================================================================
 *
 *       Filename:  HttpLogic.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/3 10:37:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/http/httplogic.h"
#include <boost/exception/diagnostic_information.hpp>
#include <cppcms/http_context.h>
#include "webgame/message/MessageBuilder.h"
#include "webgame/server/LoggerUtility.h"
#include "webgame/server/stock/HttpMessage.pb.h"
#include "webgame/utility/PageParser.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::Http::HttpLogic

THIS_CLASS::~HttpLogic() {}

THIS_CLASS::HttpLogic(cppcms::service& srv, const std::string& initFile) :
  m_service(srv),
  m_initFile(initFile),
  m_isRunning(true),
  m_startSessionId(0),
  m_inteval(1){
}

void THIS_CLASS::stop() {
  m_isRunning.store(false);
}

void THIS_CLASS::registerActions() {
  m_decoder->registerBuilder<WebGame::Server::Stock::HttpMessage>();
  doRegisterActions();
}

void THIS_CLASS::initDecoder() {
  m_decoder.reset(new DecoderType());
  registerActions();
  m_decoder->makeFinal();
}

void THIS_CLASS::init() {

  Utility::PageParser pp(m_initFile);
  std::string name = pp.get(std::string("Socket"), std::string("Name"), std::string());
  if(name.empty()) {
    std::cerr << "name error " << name << std::endl;
    throw std::logic_error("must use named socket");
  }
  pan::log_NOTICE("use socket name is ", name);
  std::string address  = pp.get(std::string("Socket"),
                                std::string("Address"),
                                std::string());

  pan::log_NOTICE("use socket address is ", address);
  initDecoder();
  m_socket.reset(new ZSocketType(
          *m_context,
          *m_decoder,
          name,
          address
          ));
  std::cout << "create socket ok....." << std::endl;
}

void THIS_CLASS::addSession(ContextPointer context,
                            int type,
                            const std::string& info) {
  int64_t sid = ++m_startSessionId;
  Server::Stock::HttpMessage message;
  message.set_type(type);
  message.set_session(sid);
  message.set_information(info);
  m_socket->sendMessage(message);
  context->async_on_peer_reset(
      boost::bind(
          &THIS_CLASS::removeContext,
          this,
          context));
  boost::lock_guard<boost::mutex> lock(m_mutex);
  m_sessions.left.insert(std::make_pair(sid, context));
}

void THIS_CLASS::removeContext(ContextPointer context) {
  boost::lock_guard<boost::mutex> lock(m_mutex);
  m_sessions.right.erase(context);
}

bool THIS_CLASS::initContext() {
if(m_context)
    return false;
  m_context.reset(new QSocketTraits::context_t());
  return true;
}

void THIS_CLASS::uninit() {
  m_socket.reset();
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
  m_socket->bindPollManager(mgr, boost::bind(&THIS_CLASS::handleMessage,
                                             this,
                                             _1));
}

bool THIS_CLASS::isWaitingContext(ContextPointer context) const {
  boost::lock_guard<boost::mutex> lock(m_mutex);
  return m_sessions.right.count(context) > 0;
}

THIS_CLASS::ContextPointer THIS_CLASS::releaseContext(int64_t sessionId) {
  ContextPointer context;
  boost::lock_guard<boost::mutex> lock(m_mutex);
  auto iter = m_sessions.left.find(sessionId);
  if(iter != m_sessions.left.end()) {
    context = (*iter).second;
    m_sessions.left.erase(iter);
  }
  return context;
}

void THIS_CLASS::sendMessage(ContextPointer context, const std::string& msg) {
  m_service.post([context, msg]() {
                 context->response().set_plain_text_header();
                 context->response().out() << msg;
                 context->async_complete_response();
                 });
}

void THIS_CLASS::handleMessage(std::shared_ptr<DataType> d) {
    auto db = d->constBody<WebGame::Server::Stock::HttpMessage>();
    if(db->session() == 0) {
      doDispatchServerMessage(db);
    } else if(auto context = releaseContext(db->session())) {
      doDispatch(context, db);
    } else {
      pan::log_DEBUG("context is not exist.... ignore current message.");
    }
}

void THIS_CLASS::run() {

  if(!initContext()) return;
  ZPollInManager mgr(boost::this_thread::get_id());
  try {
    init();
    bindPollManager(&mgr);
    while(m_isRunning.load()) {
      mgr.pollOne(m_inteval);
    }
    uninit();
  } catch(...) {
    std::cerr << "Unhandled exception!" << " " <<
      boost::current_exception_diagnostic_information() << std::endl;
    pan::log_ERROR("excpetion ", boost::current_exception_diagnostic_information());
  }
}


#undef THIS_CLASS
