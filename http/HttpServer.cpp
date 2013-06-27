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
#include "webgame/server/ServerOption.h"
#include "webgame/server/stock/HttpMessage.pb.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::Http::HttpDealer

THIS_CLASS::~HttpDealer() {}


THIS_CLASS::HttpDealer(const ServerOption& option) : m_isRunning(true) {
  init(option);
}

void THIS_CLASS::init(const ServerOption& option) {

}


void THIS_CLASS::operator()(const HttpServer::request& req,
                            HttpServer::connection_ptr conn) {
  std::cout << "call here ..... " << isRunning() << std::endl;
  if(isRunning()) {
    conn->read();
    doWork(req, conn);
  }
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {

}

void THIS_CLASS::pushMessage(const HttpServer::request& req,
                             const HttpServer::connection_ptr& conn) {
  auto message = std::make_shared<HttpMessage>();
  ++m_startId;
  message->Id = m_startId.load();
  std::cout << "method " << req.method << std::endl;
  std::cout << "source " << req.source << std::endl;
  for(auto& header : req.headers) {
    std::cout << "name " << header.name << std::endl;
    std::cout << "value " << header.value << std::endl;
  }
  std::cout << "des " << req.destination << std::endl;
  std::cout <<"body is "<< req.body << std::endl;
  message->Information = req.body;
  message->Connection = conn;
  boost::lock_guard<boost::mutex> lock(m_mutex);
}

#undef THIS_CLASS
