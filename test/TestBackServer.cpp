/*
 * =====================================================================================
 *
 *       Filename:  TestBackServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/24 16:28:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/test/TestBackServer.h"
#include "webgame/message/MessageBuilder.h"
#include "webgame/message/DataCache.h"
#include "webgame/message/MakeCacheMessage.h"
#include "webgame/protocal/PingPong.pb.h"
#include "webgame/protocal/InnerLogin.pb.h"
#include "webgame/protocal/InnerLoginResult.pb.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS TestBackServer
using WebGame::player_tt;

void THIS_CLASS::doInitCallback() {
  decoder().registerBuilder<WebGame::Protocal::PingPong>();
  registerConnectionMessageCallback(WebGame::Protocal::PingPong::value,
      [this](const MessageDealerType::ParamType& msg) {
        const auto& name = msg.first;
        const auto& db = msg.second;
        this->sendMessage(name, WebGame::Message::makeCached(*db));
      });
  decoder().registerBuilder<WebGame::Protocal::InnerLogin>();
  registerConnectionMessageCallback(WebGame::Protocal::InnerLogin::value,
                                    boost::bind(&THIS_CLASS::handleInnerLogin,
                                                this,
                                                _1));
}

void THIS_CLASS::handleInnerLogin(const MessageDealerType::ParamType& param) {
  const auto& name = param.first;
  const auto& db = param.second;
  auto innerLogin = db->constBody<WebGame::Protocal::InnerLogin>();
  WebGame::Protocal::InnerLoginResult result;
  if(hasPlayer(innerLogin->name())) {
    result.set_result(false);
    result.set_failed_reason(result.RELOGIN);
  } else {
    result.set_result(true);
    result.set_session(innerLogin->session());
    result.set_back_session(m_startSessionId++);
    result.set_id(m_startSessionId);
    result.set_property(innerLogin->property());
    m_players.insert(std::make_pair(innerLogin->name(), player_tt(m_startSessionId)));
    m_names.insert(std::make_pair(player_tt(m_startSessionId), innerLogin->name()));
  }
  sendMessage(name, result);
}
