/*
 * =====================================================================================
 *
 *       Filename:  TestBackServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/24 16:24:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_TEST_BACKSERVER_H
#define FND_TEST_BACKSERVER_H
#include "webgame/server/DefaultZBackServer.h"
class TestBackServer : public WebGame::Server::DefaultZBackServer {
  public:
    typedef WebGame::Server::DefaultZBackServer base_class;
    TestBackServer(OptionType const& option) : base_class(option) {}
  private:
    virtual void doInitCallback();
};
#endif
