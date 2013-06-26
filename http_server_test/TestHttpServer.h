/*
 * =====================================================================================
 *
 *       Filename:  TestHttpServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/26 16:03:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TESTHTTPSERVER_H
#define FND_WEBGAME_TESTHTTPSERVER_H
#include <iostream>
#include "webgame/http/HttpServer.h"

class TestHttpDealer : public WebGame::Server::Http::HttpDealer {
  public:
    typedef WebGame::Server::Http::HttpDealer base_class;
    TestHttpDealer(WebGame::Server::ServerOption& option) :
      base_class(option) {}
  private:
    virtual void doWork(const base_class::request& req,
                        const base_class::connection_ptr& conn) {
      std::cout << "doWork.....\n";
      pushMessage(req, conn);
    }
};
#endif
