/*
 * =====================================================================================
 *
 *       Filename:  TestServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年05月31日 22时19分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "TestServer.h"
#include <iostream>
#include "webgame/netcore/Connection.h"
#include "webgame/protocal/PingPong.pb.h"
#include "webgame/protocal/Login.pb.h"
#include "webgame/protocal/LoginResult.pb.h"
#include "webgame/protocal/InnerLogin.pb.h"
#include "webgame/message/MessageBuilder.h"
#include "webgame/server/ServerOption.h"
#include "webgame/protocal/InnerLoginResult.pb.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS TestServer
using WebGame::player_tt;
using namespace WebGame::Protocal;

void THIS_CLASS::doDefaultBackMessageCallback(const DataType&) const {

}
void THIS_CLASS::doSendMessageToAllConnection(const DataType& db) const {

}
void THIS_CLASS::doOnConnectionLeave(const NetErrorType& error,
    NetConnectionPointer nc) {

  removePlayerFromPlayerSet(nc);
  std::cout << "client leave " << error.message() << std::endl;

}
bool THIS_CLASS::doIsValidMessage(const DataType& db,
    NetConnectionPointer nc) const {
  return (db.headerId() != 0 &&
          db.messageType() != WebGame::Protocal::Login::value) ||
         (db.headerId() == 0 &&
          db.messageType() == WebGame::Protocal::Login::value);
}

bool THIS_CLASS::doIsRegisterConnection(NetConnectionPointer nc) const {
  return true;
}
void THIS_CLASS::doRegisterActions() {
  frontDecoder().registerBuilder<WebGame::Protocal::PingPong>();
  registerConnectionMessageCallback(WebGame::Protocal::PingPong::value,
      [this](MessageHandlerType msg) {
      const auto& db = std::get<0>(msg);
      auto conn = std::get<1>(msg);
      std::cout << db.debugString() << std::endl;
      pushMessageToBack(db);
      });
  frontDecoder().registerBuilder<WebGame::Protocal::Login>();
  registerConnectionMessageCallback(WebGame::Protocal::Login::value,
                                    boost::bind(&THIS_CLASS::handleLogin,
                                                this,
                                                _1));


  backDecoder().registerBuilder<WebGame::Protocal::InnerLoginResult>();
  registerBackMessageCallback(InnerLoginResult::value,
                              boost::bind(&THIS_CLASS::handleBack_InnerLoginResult,
                                          this,
                                          _1));

}

void THIS_CLASS::handleBack_InnerLoginResult(
    const DataType& db) {
  PANTHEIOS_ASSERT(false);
}

void THIS_CLASS::handleLogin(MessageHandlerType param) {
  const auto& db = std::get<0>(param);
  auto msg = db.constBody<WebGame::Protocal::Login>();
  auto conn = std::get<1>(param);
  std::cout << "handleLogin "
    << msg->name() << " "
    << msg->key() << " "
    << msg->property() << std::endl;
  player_tt pid = db.headerId();
  if(hasLoginnedPlayer(pid)) {
    WebGame::Protocal::LoginResult result;
    result.set_ok(false);
    result.set_failed_reason(result.RELOGIN);
    conn->sendAsyncMessage(result);
  } else {
    auto p = makeClientLoginning(conn);
    WebGame::Protocal::InnerLogin innerLogin;
    innerLogin.set_name(msg->name());
    innerLogin.set_key(msg->key());
    innerLogin.set_session(p->session());
    innerLogin.set_property(msg->property());
    pushMessageToBack(innerLogin);
  }
}

void THIS_CLASS::doDealBackServerPostMessage(const DataType& db,
    PlayerGroup const&) {
}

void THIS_CLASS::doDealBackServerGroupMessage(const MiniGroup& group,
    const DataType& db,
    PlayerGroup const&) {

}
void THIS_CLASS::removePlayerFromPlayerSet(NetConnectionPointer nc) {
  if(m_justConnected.erase(nc) == 0) {
    if(m_justLoggining.erase(nc) == 0) {
      if(m_justLoggined.erase(nc) == 0) {
        pan::log_WARNING("nc not exist .... error");
      }
    }
  }
}

WebGame::Server::FrontClientStub::pointer
THIS_CLASS::justConnectedPlayer(NetConnectionPointer nc) {
  auto iter = m_justConnected.find(nc);
  if(iter == m_justConnected.end()) return FrontClientStub::pointer();
  return *iter;
}

WebGame::Server::FrontClientStub::pointer
THIS_CLASS::justLoginningPlayer(int64_t sessionId) {
  auto iter = m_justLoggining.get<2>().find(sessionId);
  if(iter == m_justLoggining.get<2>().end()) return FrontClientStub::pointer();
  return *iter;
}

bool THIS_CLASS::hasLoginnedPlayer(player_tt pid) const {
  return m_justLoggined.get<1>().count(pid) > 0;
}

bool THIS_CLASS::hasLoginnedPlayer(int64_t sessionId) const {
  return m_justLoggined.get<2>().count(sessionId) > 0;
}

bool THIS_CLASS::removeJustLoginningPlayer(FrontClientStub::pointer p) {
  return m_justLoggining.erase(p->connection()) > 0;
}

WebGame::Server::FrontClientStub::pointer
THIS_CLASS::makeClientLoginning(NetConnectionPointer nc) {
  auto player = justConnectedPlayer(nc);
  if(player) {
    removeJustConnectPlayer(nc);
    player->setSession(m_startSessionId);
    m_startSessionId += 2;
    m_justLoggining.insert(player);
  } else {
    pan::log_DEBUG("makeClientLoginning player disappeared ");
  }
  return player;
}


WebGame::Server::FrontClientStub::pointer
THIS_CLASS::makeClientLoginned(int64_t sessionId, player_tt pid, LoginType type) {
  auto player = justLoginningPlayer(sessionId);
  if(player) {
    if(hasLoginnedPlayer(pid)) {
      if(type == LoginType::Forced) {
      }
    }
    removeJustLoginningPlayer(player);
    m_justLoggined.insert(player);
  } else {
    pan::log_DEBUG("session player ", pan::i(sessionId), " has disappeared.");
  }
  return player;
}

void THIS_CLASS::doMakeConnectionValid(NetConnectionPointer nc) {
  m_justConnected.insert(FrontClientStub::create(nc));
}
void THIS_CLASS::removeJustConnectPlayer(NetConnectionPointer nc) {
  removePlayerFromSet(m_justConnected, nc);
}


THIS_CLASS::TestServer(const OptionType& option) :
  DefaultZFrontServer(option),
  m_startSessionId(1){}

#undef THIS_CLASS
