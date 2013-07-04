/*
 * =====================================================================================
 *
 *       Filename:  TestLogic.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/4 16:57:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/http_server_test/TestLogic.h"
#include <cppcms/http_context.h>
#include <cppcms/http_response.h>
#include "webgame/server/stock/HttpMessage.pb.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS TestLogic

THIS_CLASS::~TestLogic() {}

THIS_CLASS::TestLogic(cppcms::service& srv, const std::string& initFile) :
  base_class(srv, initFile) {
}

void THIS_CLASS::doDispatch(ContextPointer context,
                const MessagePointer& msg) {
  std::cout << "call here msg is " << msg->information() << " ok \n";
  context->response().set_plain_text_header();
  context->response().out() << msg->information();
  context->async_complete_response();
}

#undef THIS_CLASS
