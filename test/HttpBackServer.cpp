/*
 * =====================================================================================
 *
 *       Filename:  HttpBackServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/1 20:07:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/test/HttpBackServer.h"
#include <iostream>
#include "webgame/server/ServerOption.h"
#include "webgame/server/stock/HttpMessage.pb.h"
#include "webgame/message/MessageBuilder.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS HttpBackServer

THIS_CLASS::HttpBackServer(const OptionType& option) :
    base_class(option) {}

THIS_CLASS::~HttpBackServer() {}


void THIS_CLASS::doInitCallback() {
  decoder().registerBuilder<WebGame::Server::Stock::HttpMessage>();
  registerConnectionMessageCallback(WebGame::Server::Stock::HttpMessage::value,
      [this](const MessageDealerType::ParamType& msg) {
        const auto& name = msg.first;
        const auto& db = msg.second;
        auto httpMessage = db->constBody<WebGame::Server::Stock::HttpMessage>();
        std::cout << "session id " << httpMessage->session()
        << " type " << httpMessage->type()
        << " information " << httpMessage->information() << std::endl;
      });
}

#undef THIS_CLASS
