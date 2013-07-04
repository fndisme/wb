/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/26 11:05:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
#include <memory>
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include "webgame/server/LoggerUtility.h"
#include "webgame/http/HttpServer.h"
#include "webgame/http_server_test/TestLogic.h"
#include <pantheios/backends/bec.file.h> // for logger
#include <boost/asio/impl/src.hpp>
PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "http";

boost::function<void ()> signalHandle;

void signalHandler(int sig) {
  std::cout << "call signal......" << std::endl;
  signalHandle();
}

int main(int argc, char** argv) {
  std::string logFile("http.log");
//  signal(SIGABRT, signalHandler);
//  signal(SIGINT, signalHandler);
  pantheios_be_file_setFilePath(logFile.c_str(),
                                PANTHEIOS_BE_FILE_F_TRUNCATE,
                                PANTHEIOS_BE_FILE_F_TRUNCATE,
                                0);

    cppcms::service srv(argc,argv);
    using WebGame::Server::Http::HttpServer;
    TestLogic l(srv, "http.js");
    HttpServer* s = new HttpServer(srv, l);
    booster::intrusive_ptr<HttpServer> httpServer(s);
    srv.applications_pool().mount(httpServer);

    boost::thread t(boost::bind(&TestLogic::run, &l));
    srv.run();
    l.stop();
    t.join();
    pan::log_DEBUG("quit normal");
    return 0;
}
