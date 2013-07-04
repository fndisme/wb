/*
 * =====================================================================================
 *
 *       Filename:  TestLogic.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/4 16:51:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_TESTLOGIC_H
#define FND_TESTLOGIC_H
#include "webgame/http/HttpLogic.h"
class TestLogic : public WebGame::Server::Http::HttpLogic {
public:
  TestLogic(cppcms::service& srv, const std::string& initFile);
  ~TestLogic();
private:
  typedef WebGame::Server::Http::HttpLogic base_class;
  void doDispatch(ContextPointer, const MessagePointer&);
};
#endif
