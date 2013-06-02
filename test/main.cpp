#include <iostream>
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/pan.hpp>
#include	<pantheios/inserters.hpp>
#include <pantheios/backends/bec.file.h>
#include <boost/asio/impl/src.hpp>
#include "webgame/message/MessageBuilder.h"
#include "TestServer.h"

PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "TestServer";
using namespace std;

int main(int argc, char** argv) {
  using namespace WebGame::Message;
  std::string logFile("TS%D-%T.log");
  
  pantheios_be_file_setFilePath(logFile.c_str(),
      PANTHEIOS_BE_FILE_F_TRUNCATE,
      PANTHEIOS_BE_FILE_F_TRUNCATE,
      0);
  boost::asio::io_service io_service;
  boost::asio::strand strand(io_service);

  MessageBuilder builder;
  


  TestServer::OptionType option(
      "TestServer.json",
      &io_service,
      nullptr,
      &builder,
      &strand,
      &strand);

  std::cout << "start the server\n";
  TestServer server(option);
  server.start();
  std::cout << "ok start io\n";

  io_service.run();
  return 0;
}
