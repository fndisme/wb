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
#include <atomic>
#include <memory>
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <string>
#include <iostream>
#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include "webgame/server/ServerOption.h"
#include "webgame/http_server_test/TestHttpServer.h"
#include <pantheios/backends/bec.file.h> // for logger
#include <boost/asio/impl/src.hpp>
#include <xs.hpp>
PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "http";


int main(int argc, char** argv) {
  std::string logFile("http.log");

  pantheios_be_file_setFilePath(logFile.c_str(),
                                PANTHEIOS_BE_FILE_F_TRUNCATE,
                                PANTHEIOS_BE_FILE_F_TRUNCATE,
                                0);
    xs::context_t ctx;
    boost::asio::io_service io_service;
    boost::asio::strand strand(io_service);
    WebGame::Server::ZPollInManager poller(boost::this_thread::get_id());

    WebGame::Server::ServerOption option(
        "TestServer.json",
        &io_service,
        &ctx,
        &strand,
        &strand);


    using namespace boost::network::http; // parameters are in this namespace
    boost::network::utils::thread_pool pool(2);
    TestHttpDealer dealer(option);
    WebGame::Server::Http::HttpServer instance(_address="0.0.0.0", _port="8080",
                                               _handler=dealer,
                                               _io_service=io_service,
                                               _thread_pool=pool,
                                               _reuse_address=true);
    instance.run();

    return 0;
}
