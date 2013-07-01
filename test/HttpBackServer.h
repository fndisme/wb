/*
 * =====================================================================================
 *
 *       Filename:  HttpBackServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/1 20:06:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_HTTPBACKSERVER_H
#define FND_HTTPBACKSERVER_H
#include <string>
#include <map>
#include <set>
#include "webgame/server/DefaultZBackServer.h"
class HttpBackServer : public WebGame::Server::DefaultZBackServer {
  public:
    typedef WebGame::Server::DefaultZBackServer base_class;
    HttpBackServer(OptionType const& option);
    ~HttpBackServer();
  private:
    virtual void doInitCallback();
};
#endif
