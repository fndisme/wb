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
}
