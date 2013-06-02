/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-2 13:56:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#define PANTHEIOS_NO_INCLUDE_OS_AND_3PTYLIB_STRING_ACCESS
/*
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#ifdef WIN32
#include "tcmalloc.h"
#include	"google/malloc_extension.h"
#else
#include <gperftools/tcmalloc.h>
#include <gperftools/malloc_extension.h>
#endif
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/impl/src.hpp>
#include <boost/thread.hpp>
#include	<boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <pantheios/pantheios.hpp>
#include	<pantheios/inserters.hpp>
#include	<pantheios/inserters/i.hpp>
#include <platformstl/platformstl.h>
#include <pantheios/backends/bec.fprintf.h>
#include <vector>
#include	"webgame/utility/PageParser.h"
#include	"TestClient.h"
#include "webgame/message/MessageBuilder.h"
#include <type_traits>
#include "webgame/message/DataBlock.h"
#include "webgame/protocal/PingPong.pb.h"

PANTHEIOS_EXTERN_C const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "login_client" ;


enum {
	beid_Console = 1,
	beid_File = 2
} ;

struct runner {
	void run() const {
		m_io_service.run() ;
	}

	runner(boost::asio::io_service& io) : m_io_service(io) {}
	boost::asio::io_service& m_io_service ;
} ;

enum {max_client_player = 1 } ;
int main(int argc, char** argv) {
  try {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::string file_name = argc < 2 ? "client.json" : argv[1] ;
    using boost::asio::ip::tcp ;

    // just for test.....
    using std::shared_ptr ;
    boost::mutex mutex ; 


    std::vector<std::shared_ptr<TestClient> > clients ;

    boost::asio::io_service io_service ;
    boost::asio::strand strand(io_service);
    shared_ptr<boost::asio::io_service::work>
      work(new boost::asio::io_service::work(io_service)) ;
    runner r1(io_service) ;
    WebGame::Utility::PageParser pp(file_name) ;
    size_t max_player_num = pp.get("test", "max_player_num", 1) ;
    size_t start_player_id = pp.get("test", "start_player_id", 100) ;
    const std::string quick_command = pp.get("test", "quick_command", 
        std::string("login fndisgod")) ;

    WebGame::Message::MessageBuilder builder;

    builder.registerBuilder<WebGame::Protocal::PingPong>();
    builder.makeFinal();
    for(int i = 0 ; i < static_cast<int>(max_player_num); ++i) {
      clients.push_back(std::shared_ptr<TestClient>(
            new TestClient(io_service, strand, strand,
              file_name,
              WebGame::player_tt(start_player_id + i), 
              mutex,
              builder))) ;
    }

    boost::thread t(boost::bind(&runner::run, &r1));

    for(auto client : clients)
      client->start() ;

    //login_client.update() ;
    while(true) {
      std::cout << "cmd > " ;
      std::string input_cmd ;
      {
        std::getline(std::cin, input_cmd) ;
      }
      if(input_cmd.empty()) {
        continue ;
      }
      for(auto client : clients)
        client->outside_command(input_cmd) ;
    }
    work.reset() ;
    io_service.stop();
    t.join() ;
  } catch(std::exception& e) {
    std::cout << "login_client error : " << e.what() << std::endl ;
    pantheios::log_ERROR(e) ;
  }
  return 0 ;
}

