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
#include <cppcms/service.h>
#include <cppcms/url_dispatcher.h>
#include <cppdb/frontend.h>
#include "webgame/server/ServerOption.h"
#include "webgame/server/LoggerUtility.h"
#include "webgame/server/ZPollInManager.h"

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
    m_startSessionId(0),
    m_receiveSessionId(0){
    dispatcher().assign("/get/(\\d+)", &THIS_CLASS::get, this, 1);
    dispatcher().assign("/post", &THIS_CLASS::post,this);
    dispatcher().assign(".*",&THIS_CLASS::redirect,this);
    initDb();
}

void THIS_CLASS::get(std::string no) {
    int id = atoi(no.c_str());
    if(id > m_receiveSessionId) {
        response().status(404);
        return;
    } else if(id < m_receiveSessionId) {
        response().set_plain_text_header();
        response().out() << m_receiveMessage[id]->information();
        return;
    } else {
        auto context = release_context();
        context->async_on_peer_reset(
            boost::bind(
                &THIS_CLASS::removeContext,
                booster::intrusive_ptr<THIS_CLASS>(this),
                context));
        boost::lock_guard<boost::mutex> lock(m_mutex);
    }
}

void THIS_CLASS::redirect() {
    response().set_redirect_header("/the_chat.html");
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
        << m_startSessionId.load() << 1 << now << info;
    stat.exec();
}

void THIS_CLASS::handlePost() {
  booster::shared_ptr<cppcms::http::context> context=release_context();
  int64_t sessionId = ++m_startSessionId;
  MessagePointer msg = std::make_shared<WebGame::Server::Stock::HttpMessage>();
  StockMessage stockMsg = std::make_pair(context, msg);
  msg->set_session(sessionId);
  msg->set_type(0);
  msg->set_information(context->request().post("message"));
  recordInformation(msg->information());
  m_socket->sendMessage(*msg);
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
