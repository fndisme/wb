#include <signal.h>
#include <iostream>
#include <boost/asio.hpp> // for include compile error
#include <boost/exception/diagnostic_information.hpp>
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/pan.hpp>
#include	<pantheios/inserters.hpp>
#include <pantheios/backends/bec.file.h>
#include <boost/asio/impl/src.hpp>
#include <xs.hpp>
#include "webgame/message/MessageBuilder.h"
#include "webgame/server/DefaultZBackServer.h"
#include "webgame/server/ServerOption.h"
#include "webgame/server/ZPollInManager.h"
//#include "TestServer.h"
//#include "TestBackServer.h"
#include "HttpBackServer.h"

static bool is_running = true;

void signalHandler(int sig) {
  is_running = false;
}


PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "TestServer";
using namespace std;

int main(int argc, char** argv) {
  signal(SIGABRT, signalHandler);
  signal(SIGINT, signalHandler);
  try {
    using namespace WebGame::Message;
    std::string logFile("TS%D-%T.log");

    pantheios_be_file_setFilePath(logFile.c_str(),
                                  PANTHEIOS_BE_FILE_F_TRUNCATE,
                                  PANTHEIOS_BE_FILE_F_TRUNCATE,
                                  0);
    xs::context_t ctx;
    boost::asio::io_service io_service;
    boost::asio::strand strand(io_service);
    WebGame::Server::ZPollInManager poller(boost::this_thread::get_id());

//    TestServer::OptionType option(
//        "TestServer.json",
//        &io_service,
//        &ctx,
//        &strand,
//        &strand);
//
//    std::cout << "start the server\n";
//
    HttpBackServer::OptionType option2(
        "httpBackServer.json",
        &io_service,
        &ctx,
        &strand,
        &strand);

    //TestServer server(option);
    HttpBackServer backServer(option2);
    backServer.start();
    //server.start();
    std::cout << "ok start io\n";
    backServer.bindPollManager(&poller);
    //server.bindPollManager(&poller);

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
    while(is_running) {
      poller.poll(1);
    }
    io_service.stop();
    t.join();
    std::cout << "dead normal\n";
  } catch(...) {
    std::cerr << "Unhandled exception!" << std::endl <<
      boost::current_exception_diagnostic_information();
  }
  std::cout << "good bye\n";
  return 0;
}
