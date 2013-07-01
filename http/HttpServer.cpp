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
#include "webgame/server/ServerOption.h"
#include "webgame/server/LoggerUtility.h"
#include "webgame/server/ZPollInManager.h"
#include <cppcms/http_response.h>
#include "webgame/server/stock/HttpMessage.pb.h"

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
  while(m_isRunning.load()) {
    mgr.pollOne(1);
  }
  std::cout << "bye" << std::endl;
}

void THIS_CLASS::main(std::string url) {
  response().out()<<
    "<html>\n"
    "<body>\n"
    "  <h1>Hello World</h1>\n"
    "</body>\n"
    "</html>\n";
}
#undef THIS_CLASS
