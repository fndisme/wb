/*
 * =====================================================================================
 *
 *       Filename:  HttpServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/26 14:53:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/http/HttpServer.h"
#include <iostream>
#include <boost/bind.hpp>
#include <cppcms/http_response.h>
#include <cppcms/http_context.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppdb/frontend.h>
#include "webgame/server/ServerOption.h"
#include "webgame/server/LoggerUtility.h"
#include "webgame/server/ZPollInManager.h"
#include "webgame/message/MessageBuilder.h"
#include "webgame/utility/PageParser.h"
#include "webgame/server/stock/HttpMessage.pb.h"
#include <boost/exception/diagnostic_information.hpp>

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::Http::HttpServer

THIS_CLASS::~HttpServer() {}


THIS_CLASS::HttpServer(cppcms::service& srv,
                       const std::string& initFile) :
    base_class(srv),
    m_context(nullptr),
    m_isRunning(true),
    m_initFile(initFile),
    m_startSesionId(0){
    dispatcher().assign("/get/(\\d+)", &THIS_CLASS::get, this, 1);
    dispatcher().assign("/post", &THIS_CLASS::post,this);
    dispatcher().assign(".*",&THIS_CLASS::redirect,this);
    initDb();
}

void THIS_CLASS::get(std::string no) {
    response().status(404);
}

void THIS_CLASS::redirect() {
    std::cout << "call redirect" << std::endl;
    response().set_redirect_header("/the_chat.html");
}

void THIS_CLASS::transferMessageWithOther() {
  pan::log_DEBUG("start transferMessageWithOther");
  if(m_context)
    return;
  m_context.reset(new QSocketTraits::context_t());
  ZPollInManager mgr(boost::this_thread::get_id());
  try {
    initResource();
    bindPollManager(&mgr);
    while(m_isRunning.load()) {
      mgr.pollOne(1);
    }
    releaseResource();
  } catch(...) {
    std::cerr << "Unhandled exception!" << " " <<
            boost::current_exception_diagnostic_information() << std::endl;
    pan::log_ERROR("excpetion ", boost::current_exception_diagnostic_information());
  }
  std::cout << "bye" << std::endl;
}

void THIS_CLASS::removeContext(booster::shared_ptr<cppcms::http::context> context) {
  auto iter = m_contextPointers.find(context);
  if(iter != m_contextPointers.end()) {
      for(auto index : (*iter).second)
        m_stockMessages.erase(index);
      m_contextPointers.erase(iter);
  }
}

void THIS_CLASS::registerActions() {
  m_decoder->registerBuilder<WebGame::Server::Stock::HttpMessage>();
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
  m_socket->bindPollManager(mgr);
}

void THIS_CLASS::initResource() {
  m_decoder.reset(new DecoderType());
  registerActions();
  m_decoder->makeFinal();
  Utility::PageParser pp(m_initFile);
  std::string name = pp.get(std::string("Socket"), std::string("Name"), std::string());
  if(name.empty()) {
    throw std::logic_error("must use named socket");
  }
  pan::log_NOTICE("use socket name is ", name);
  std::string address  = pp.get(std::string("Socket"),
                                std::string("Address"),
                                std::string());

  pan::log_NOTICE("use socket address is ", address);
  m_socket.reset(new ZSocketType(
          *m_context,
          *m_decoder,
          name,
          address
          ));
}

void THIS_CLASS::releaseResource() {
  m_socket.reset();
  m_decoder.reset();
}

void THIS_CLASS::recordInformation(const std::string& info) {
    std::time_t now_time = std::time(0);
    std::tm now = *std::localtime(&now_time);
    cppdb::statement stat;
    stat = (*m_dbSession) <<
        "INSERT INTO test(sessionId,who,t,information) "
        "VALUES(?,?,?,?)"
        << m_startSesionId << 1 << now << info;
    stat.exec();
}

void THIS_CLASS::handlePost() {
  booster::shared_ptr<cppcms::http::context> context=release_context();
  ++m_startSesionId;
  MessagePointer msg = std::make_shared<WebGame::Server::Stock::HttpMessage>();
  StockMessage stockMsg = std::make_pair(context, msg);
  msg->set_session(m_startSesionId);
  msg->set_type(0);
  msg->set_information(context->request().post("message"));
  m_contextPointers[context].push_back(m_startSesionId);
  m_stockMessages.insert(std::make_pair(m_startSesionId, stockMsg));
  recordInformation(msg->information());
  m_socket->sendMessage(*msg);
  context->async_on_peer_reset(
      boost::bind(
          &THIS_CLASS::removeContext,
          booster::intrusive_ptr<THIS_CLASS>(this),
          context));
}

void THIS_CLASS::post() {
  if(request().request_method() == "POST") {
      std::cout << "handle request" << std::endl;
      handlePost();
  }
}

void THIS_CLASS::initDb() {
    try {
        m_dbSession.reset(new cppdb::session("sqlite3:db=db.db"));
        auto& sql = *m_dbSession;
        sql << "DROP TABLE IF EXISTS test" << cppdb::exec;
        sql<<   "CREATE TABLE test ( "
            "   id   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "   sessionId    INTEGER,"
            "   who    INTEGER, "
            "   t    TIMESTAMP,"
            "   information TEXT "
            ")  " << cppdb::exec;
    } catch (std::exception& error) {
        std::cerr << "error " << error.what() << std::endl;
    }
}

void THIS_CLASS::main(std::string url) {
      base_class::main(url);
//  response().out()<<
//    "<html>\n"
//    "<body>\n"
//    "  <h1>Hello World</h1>\n"
//    "</body>\n"
//    "</html>\n";
//
}
#undef THIS_CLASS
