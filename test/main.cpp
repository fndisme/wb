#include <iostream>
#include <boost/asio.hpp> // for include compile error
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/pan.hpp>
#include	<pantheios/inserters.hpp>
#include <pantheios/backends/bec.file.h>
#include <boost/asio/impl/src.hpp>
#include "webgame/message/MessageBuilder.h"
#include "webgame/server/DefaultZBackServer.h"
#include "webgame/server/ServerOption.h"
#include "webgame/server/ZPollInManager.h"
#include "TestServer.h"


PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "TestServer";
using namespace std;

class BackServer : public WebGame::Server::DefaultZBackServer {
  
  public:
    typedef WebGame::Server::DefaultZBackServer base_class;
    BackServer(OptionType const& option) : base_class(option) {}

};

int main(int argc, char** argv) {
  using namespace WebGame::Message;
  std::string logFile("TS%D-%T.log");

  pantheios_be_file_setFilePath(logFile.c_str(),
      PANTHEIOS_BE_FILE_F_TRUNCATE,
      PANTHEIOS_BE_FILE_F_TRUNCATE,
      0);
  boost::asio::io_service io_service;
  boost::asio::strand strand(io_service);
  WebGame::Server::ZPollInManager poller(boost::this_thread::get_id());

  TestServer::OptionType option(
      "TestServer.json",
      &io_service,
      nullptr,
      &strand,
      &strand);

  std::cout << "start the server\n";
  TestServer server(option);
  BackServer backServer(option);
  backServer.start();
  server.start();
  std::cout << "ok start io\n";
  backServer.bindPollManager(&poller);
  server.bindPollManager(&poller);

  boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
  while(true) {
    poller.poll(1);
  }
  io_service.stop();
  t.join();
  return 0;
}
