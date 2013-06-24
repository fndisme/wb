/*
 * =====================================================================================
 *
 *       Filename:  TestClient.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年06月02日 17时58分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "TestClient.h"
#include "webgame/protocal/PingPong.pb.h"
#include "webgame/protocal/Login.pb.h"
namespace {
  const std::string PingPong("pingpong");
  const std::string Login("login");
}

bool TestClient::doParse(
    const std::string& cmd,
    const std::vector<std::string>& params, WebGame::Message::DataBlock& db, int& who) {
  try {
  if(cmd == PingPong && params.size() == 2) {
    auto pingpong = std::make_shared<WebGame::Protocal::PingPong>();
    pingpong->set_information(params[1]);
    db.setBody(pingpong);
  } else if(cmd == Login && params.size() > 3) {
    auto login = std::make_shared<WebGame::Protocal::Login>();
    login->set_name(params[1]);
    login->set_key(params[2]);
    db.setHeaderId(0);
    db.setBody(login);
  }
  return true;
  } catch(...) {
    pan::log_DEBUG("has error");
    return false;
  }
}

void TestClient::doInitHandler() {
  addHandler(WebGame::Protocal::PingPong::value, [](message_handler_parameter_type param) {
      const auto& msg = std::get<0>(param);
      auto conn = std::get<1>(param);
      conn->sendAsyncMessage(msg);
      });


}

TestClient::TestClient(boost::asio::io_service& io,
        boost::asio::strand& readStrand,
        boost::asio::strand& writeStrand,
        const std::string& init_file, WebGame::player_tt id,
        boost::mutex& mutex,
        const DecoderType& decoder
        ):
      WebGame::Mock::DummyClient(io, readStrand, writeStrand, init_file, id, mutex, decoder) {}
