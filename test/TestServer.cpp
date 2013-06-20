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
#include "webgame/message/MessageBuilder.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS TestServer
using WebGame::player_tt;

void THIS_CLASS::doDefaultBackMessageCallback(const DataType&) const {

}
void THIS_CLASS::doSendMessageToAllConnection(const DataType& db) const {

}
void THIS_CLASS::doOnConnectionLeave(const NetErrorType& error,
    NetConnectionPointer nc) {
  std::cout << "client leave " << error.message() << std::endl;

}
bool THIS_CLASS::doIsValidMessage(const DataType& db,
    NetConnectionPointer nc) const {
  return true;
}
bool THIS_CLASS::doIsRegisterConnection(NetConnectionPointer nc) const {
  return true;
}
void THIS_CLASS::doRegisterActions() {
  decoder()->registerBuilder<WebGame::Protocal::PingPong>();
  registerConnectionMessageCallback(WebGame::Protocal::PingPong::value,
      [](MessageHandlerType msg) {
      const auto& db = std::get<0>(msg);
      auto conn = std::get<1>(msg);
      std::cout << db.debugString() << std::endl;
      conn->sendAsyncMessage(db);
      });

}

void THIS_CLASS::doDealBackServerPostMessage(const DataType& db,
    PlayerGroup const&) {
}

void THIS_CLASS::doDealBackServerGroupMessage(const MiniGroup& group,
    const DataType& db,
    PlayerGroup const&) {

}

void THIS_CLASS::doInitDecoder() {
    PANTHEIOS_ASSERT(decoder());
}

THIS_CLASS::TestServer(const OptionType& option) :
  DefaultZFrontServer(option) {}

#undef THIS_CLASS
