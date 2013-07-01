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
  m_initFile(initFile){
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
  m_contextPointers.erase(context);
}

void THIS_CLASS::registerActions() {
  m_decoder->registerBuilder<WebGame::Server::Stock::HttpMessage>();
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
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

void THIS_CLASS::main(std::string url) {
  booster::shared_ptr<cppcms::http::context> context=release_context();
  m_contextPointers[context]++;
  context->async_on_peer_reset(
      boost::bind(
          &THIS_CLASS::removeContext,
          booster::intrusive_ptr<THIS_CLASS>(this),
          context));
  response().out()<<
    "<html>\n"
    "<body>\n"
    "  <h1>Hello World</h1>\n"
    "</body>\n"
    "</html>\n";

}
#undef THIS_CLASS
