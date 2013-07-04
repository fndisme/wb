/*
 * =====================================================================================
 *
 *       Filename:  HttpMessageToJson.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/4 18:10:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_HTTPMESSAGETOJSON_H
#define FND_WEBGAME_HTTPMESSAGETOJSON_H
#include <cppcms/json.h>
#include "webgame/server/stock/HttpMessage.pb.h"
namespace cppcms { namespace json {
  template<>
    struct traits< ::WebGame::Server::Stock::HttpMessage> {
      static ::WebGame::Server::Stock::HttpMessage get(const value& v) {
        if(v.type() != is_object) throw bad_value_cast();
        ::WebGame::Server::Stock::HttpMessage msg;
        msg.set_session(v.get<int64_t>("session"));
        msg.set_type(v.get<int64_t>("type"));
        msg.set_information(v.get<std::string>("information"));
        return msg;
      }

      static void set(value& v, const WebGame::Server::Stock::HttpMessage& msg) {
        v.set("session", msg.session());
        v.set("type", msg.type());
        v.set("information", msg.information());
      }
    };
}}
#endif
