/*
 * =====================================================================================
 *
 *       Filename:  dummy_client.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-9-2 13:45:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme@163.com),
 *        Company:  GJY
 *
 * =====================================================================================
 */
#include "webgame/mock/DummyClient.h"
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/asio.hpp>
#include <pantheios/pantheios.hpp>
#include	<pantheios/pan.hpp>
#include	<pantheios/inserters.hpp>
#include	<pantheios/inserters/i.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>
#include	<boost/system/system_error.hpp>
#include "webgame/utility/PageParser.h"
#include "webgame/message/MakeCacheMessage.h"
#include	"webgame/netcore/TimerEvent.h"
#include	"webgame/server/stock/HeartBeat.pb.h"
#include	"webgame/message/MessageUtility.h"
#include "webgame/message/MessageBuilder.h"
// shims
#include	"webgame/message/shims/DataBlock.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Mock::DummyClient
THIS_CLASS::~DummyClient() {}
THIS_CLASS::DummyClient(boost::asio::io_service& io_service,
    boost::asio::strand& readStrand,
    boost::asio::strand& writeStrand,
    const std::string& init_file_name,
    WebGame::player_tt pid,
    boost::mutex& mutex,
    const DecoderType& decoder) :
  m_io_service(io_service),
  m_mutex(mutex),
  m_connection(new THIS_CLASS::ConnectionType(io_service, readStrand,
        writeStrand, decoder)),
  m_id(pid) {
    init_property(init_file_name) ;
    boost::system::error_code error = boost::asio::error::host_not_found ;
    ConnectionType::data_getter_pointer p(new ConnectionType::data_getter_type(m_connection, 4192)) ;
    p->messageDealer = boost::bind(&DummyClient::handle_server_data,
        this,
        _1,
        _2) ;
    m_connection->resetGetter(std::move(p)) ;

    m_connection->handleError.connect(boost::bind(&THIS_CLASS::handle_server_error,
          this,
          _1,
          _2));
    error = boost::asio::error::host_not_found ;

  }


void THIS_CLASS::init_property(const std::string& file_name) {
  Utility::PageParser pp(file_name) ;
  int id = pp.get<int>("player", "id") ;
  if(m_id == 0) m_id = player_tt(id)  ;
  m_server_address = pp.get("net", "server", std::string("127.0.0.1"));
  m_port =  pp.get("net", "port", std::string("9999")) ;
}


void THIS_CLASS::deal_HeartBeat(message_handler_parameter_type param) const {
  auto nc = std::get<1>(param) ;
  Server::Stock::HeartBeat hb ;
  nc->sendAsyncMessage(Message::easyDataBlockCache(hb, m_id)) ;
}


void THIS_CLASS::handle_heart_beat() {
  auto heart_beat = std::make_shared<WebGame::Server::Stock::HeartBeat>() ;
  if(m_connection) m_connection->sendAsyncMessage(m_id, heart_beat) ;
}
void THIS_CLASS::init_flash_handlers() {
  m_message_handler.add(WebGame::Server::Stock::HeartBeat::value,
      boost::bind(&THIS_CLASS::deal_HeartBeat, this, _1)) ;
  doInitHandler();
  m_message_handler.lock() ;
}


void THIS_CLASS::handle_server_error(const boost::system::error_code& error,
    THIS_CLASS::ConnectionType::pointer nc) {
  pantheios::log_ERROR("网络错误", error.message()) ;
  if(m_connection)
    m_connection.reset() ;
  }

void THIS_CLASS::handle_server_data(const THIS_CLASS::ConnectionType::data_type& db,
    THIS_CLASS::ConnectionType::pointer nc) {

  try {
    //if(db.messageType() != WebGame::Server::Stock::HeartBeat::value)
    std::cout << "handle server data ??????\n";
    pantheios::log_DEBUG("F ", db.debugString()) ;
    auto param = std::make_tuple(std::cref(db), nc) ;
    m_message_handler.dispatch(db.messageType(), param) ;
  }
  catch ( const std::exception &ExceptObj ) {		/* handle exception: */
    pantheios::log_WARNING("处理消息有意长", ExceptObj) ;
  }
  catch (...) {		/* handle exception: unspecified */
    pantheios::log_WARNING("严重错误") ;
  }
}

void THIS_CLASS::start() {
  //m_connection->start() ;
  //
  init_flash_handlers() ;
  initNetContex();
}

void THIS_CLASS::outside_command(const std::string& input_cmd) {
  Message::DataBlock db ;
  int who ;

  auto ok = parse_message(db, input_cmd, who) ;
  if(ok) {
    m_connection->sendAsyncMessage(db) ;
    pantheios::log_DEBUG("flash command ok") ;
  } else {
    pantheios::log_DEBUG("cmd is not valid") ;
  }
}

void THIS_CLASS::update() {
  std::cout << "cmd > " ;
  std::string input_cmd ;
  std::getline(std::cin, input_cmd) ;
  if(input_cmd.empty() || input_cmd[0] == 'Q') {
    std::cout << "empty command!\n" ;
    return ;
  }
  outside_command(input_cmd) ;
}


bool THIS_CLASS::parse_message(WebGame::Message::DataBlock& db, const std::string& msg, int& who) {
  std::vector<std::string> tokens ;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer ;
  boost::char_separator<char> sep(" ") ;
  tokenizer tok(msg, sep) ;
  tokens.assign(tok.begin(), tok.end()) ;
  if(tokens.size() == 0)
    return false ;
  return handle_parse_message(tokens[0], tokens, db, who) ;
}

bool THIS_CLASS::handle_parse_message(const std::string& cmd, const std::vector<std::string>& tokens,
    WebGame::Message::DataBlock& db,
    int& who) {
  using std::shared_ptr ;
  pantheios::log_DEBUG("cmd is ", cmd) ;
  db.setHeaderId(m_id) ;
  try {
    return doParse(cmd, tokens, db, who);
  } catch(std::exception& ExceptObj) {
    pantheios::log_WARNING("Failed for ", ExceptObj) ;
  }
  return false ;
}

void THIS_CLASS::initNetContex() {

  boost::system::error_code error = boost::asio::error::host_not_found ;
  m_connection->startAsyncConnect(m_server_address, m_port, error) ;
  if(error)
    throw boost::system::system_error(error) ;
  m_connection->start() ;

}

#undef THIS_CLASS
