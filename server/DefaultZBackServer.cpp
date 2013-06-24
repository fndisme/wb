/*
 * =====================================================================================
 *
 *       Filename:  DefaultZBackServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/21 11:30:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/server/DefaultZBackServer.h"
#include "webgame/message/MessageBuilder.h"
#include "webgame/netcore/TimerEvent.h"
#include "webgame/server/LoggerUtility.h"
#include "webgame/server/ServerOption.h"
#include "webgame/utility/PageParser.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

namespace {
  const std::string Net("Net");
  const std::string SecondsPerTick("SecondsPerTick");
  const std::string PublishAddress("PublishAddress");
  const std::string SocketAddress("SocketAddress");
}

#define THIS_CLASS WebGame::Server::DefaultZBackServer

THIS_CLASS::~DefaultZBackServer() NOEXCEPT {}

THIS_CLASS::DefaultZBackServer(const OptionType& option) :
  m_zeroContext(option.ZeroContext),
  m_readStrand(option.ReadStrand),
  m_writeStrand(option.WriteStrand),
  m_decoder(new DecoderType()),
  m_propertyFile(option.PropertyFileName),
  m_tickUsedSeconds(1),
  m_currentTicks(0){
  }

void THIS_CLASS::makeDecorderLocked() {
    m_decoder->makeFinal();
}

void THIS_CLASS::initProperty() {
  {
    Utility::PageParser pp(m_propertyFile) ;
    m_tickUsedSeconds = pp.get(Net, SecondsPerTick, 1);
    if(m_tickUsedSeconds <= 0) {
      pantheios::log_NOTICE("server timer seconds per ticket is not valid ",
                            pan::i(m_tickUsedSeconds),
                            " changes to 1");
      m_tickUsedSeconds = 1;
    }
    pantheios::log_NOTICE("use seconds per tick is ", pan::i(m_tickUsedSeconds));

    m_publishAddress = pp.get(Net, PublishAddress, std::string());
    m_socketAddress = pp.get(Net, SocketAddress, std::string());
    if(m_socketAddress.empty()) {
      pantheios::log_ERROR("empty socket address is not valid....");
      throw std::runtime_error("empty socket address");
    }
  }

  doInitProperty();
}

void THIS_CLASS::registerDefaultTimer() {
  m_clockTimer = NetCore::TimerEvent::create(*m_readStrand,
                                             second_tt(m_tickUsedSeconds),
                                             boost::bind(&THIS_CLASS::tick,
                                                         this));
}

void THIS_CLASS::tick() {
  ++m_currentTicks;
  pan::log_DEBUG("call tick is ", pan::i(m_currentTicks));
  m_timeoutQueue.runLoop(m_currentTicks);
  doTick();
}

void THIS_CLASS::initCallback() {
  doInitCallback();
  m_frontMessageDealer.lock();
}

void THIS_CLASS::connectToFront() {
  if(m_publishAddress.empty()) {
    m_socket.reset(new ZSocketType(*m_readStrand,
                   *m_zeroContext,
                   *m_decoder,
                   m_socketAddress));
  } else {
    m_socket.reset(new ZSocketType(*m_readStrand,
                   *m_zeroContext,
                   *m_decoder,
                   m_publishAddress,
                   m_socketAddress));
  }
}

void THIS_CLASS::init() {
  initProperty();
  registerDefaultTimer();
  initCallback();
  connectToFront();
}

void THIS_CLASS::dealFrontMessage(const std::string& frontName,
                                  std::shared_ptr<ZSocketType::ReadDataType> db) {
  FrontMessageType param = std::make_pair(std::cref(frontName), std::cref(db));
  m_frontMessageDealer.dispatch(db->messageType(), param);
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
  PANTHEIOS_ASSERT(m_socket);
  m_socket->bindPollManager(mgr, boost::bind(&THIS_CLASS::dealFrontMessage,
                                             this,
                                             _1,
                                             _2));
}


#undef THIS_CLASS
