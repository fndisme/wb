/*
 * =====================================================================================
 *
 *       Filename:  DefaultZFrontServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年03月06日 15时14分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */

#include "webgame/server/DefaultZFrontServer.h"
#include <utility>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "webgame/server/LoggerUtility.h"
#include "webgame/netcore/Acceptor.h"
#include "webgame/netcore/Connection.h"
#include "webgame/netcore/TimerEvent.h"
#include "webgame/message/shims/DataBlock.h"
#include "webgame/message/MessageBuilder.h"
#include "webgame/server/ServerOption.h"
#include "webgame/server/ZPollInManager.h"
#include "webgame/utility/LockGuard.h"
#include "webgame/utility/PageParser.h"


// base message
#include "webgame/server/stock/HeartBeat.pb.h"
#include "webgame/server/stock/InnerMessage.pb.h"
#include "webgame/server/stock/InnerPostMessage.pb.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::DefaultZFrontServer

namespace {
  const std::string FrontServerOption("FrontServerOption") ;
  const std::string Net("Net") ;
  const std::string ListenPort("ListenPort") ;
  const std::string HardPoolMessageSize("HardPoolMessageSize") ;
  const std::string MaxSendUngentMessageSize("MaxSendUngentMessageSize") ;
  const std::string MaxSendNormalMessageSize("MaxSendNormalMessageSize") ;

  const std::string IsHasBackServer("IsHasBackServer") ;
  const std::string BackServerPublishAddress("BackServerPublishAddress") ;
  const std::string BackServerSocketAddress("BackServerSocketAddress") ;
  const std::string NameOfMyself("NameOfMyself") ;

  const std::string ClientOption("ClientOption") ;
  const std::string HeartBeatRate("HeartBeatRate") ;
  const std::string MaxAnswerTime("MaxAnswerTime") ;

  const std::string PlayerHeartBeat("PlayerHeartBeat") ;
}

THIS_CLASS::~DefaultZFrontServer() NOEXCEPT {}

void THIS_CLASS::stop() {
  m_acceptor->stopAll() ;
}

THIS_CLASS::DefaultZFrontServer(const OptionType& option) :
  //m_ioService(option.IoService),
  m_port(0),
  m_zeroContext(option.ZeroContext),
  m_readStrand(option.ReadStrand),
  m_writeStrand(option.WriteStrand),
  m_decoder(new DecoderType()),
  m_socket(),
  m_propertyFile(option.PropertyFileName),
  m_client_handlers(),
  m_back_dealer_handlers(),
  m_back_subscriber_dealers(),
  m_acceptor(),
  m_timers(),
  m_nameForBackServer(),
  m_maxAnswerTime(0) ,
  m_hasBack(true),
  m_hard_system_prepared_message_limit(10000),
  m_delayActor(MaxDelayTime) {
  }

void THIS_CLASS::init() {
  registerActions() ;
  connectBack() ;
  startReceiveConnection() ;
  initOtherService() ;
  registerStockMessage() ;
  makeMessageDealersFinal() ;

}

void THIS_CLASS::registerStockMessage() {
  if(m_hasBack) {
    m_back_dealer_handlers.add(Stock::InnerMessage::value,
        boost::bind(&THIS_CLASS::handleBackInnerMessage,
          this,
          _1)) ;

    m_back_subscriber_dealers.add(Stock::InnerPostMessage::value,
        boost::bind(&THIS_CLASS::handleBackInnerPostMessage,
          this,
          _1)) ;
  }

  //if(needHeartBeat()) m_normal_messages.insert(Server::Stock::HeartBeat::value) ;
}

void THIS_CLASS::connectBack() {
  Utility::PageParser pp(m_propertyFile) ;

  m_hasBack= pp.get(Net, IsHasBackServer, 1) > 0 ;

  if(m_hasBack) {
    std::string default_address ;
    // first set sub address
    std::string radio_address =
      pp.get(Net, BackServerPublishAddress, default_address) ;

    pantheios::log_DEBUG("connect sub address is ", radio_address) ;
    PANTHEIOS_MESSAGE_ASSERT(!radio_address.empty(),
        "we need BackServerPublishAddress") ;

    // register where we get back the message
    m_nameForBackServer=
      pp.get(Net, NameOfMyself, default_address) ;
    PANTHEIOS_MESSAGE_ASSERT(!m_nameForBackServer.empty(),
        "we need NameOfMyself has a ****name****") ;
    // set name tell back who am I.
    std::string socket_address =
      pp.get(Net, BackServerSocketAddress, default_address) ;
    pantheios::log_DEBUG("connect back poster is ", socket_address) ;
    PANTHEIOS_MESSAGE_ASSERT(!socket_address.empty(),
        "we need BackServerPosterAddress") ;

    PANTHEIOS_ASSERT(m_zeroContext) ;

    m_socket.reset(
        new ZSocketType(
          *m_readStrand,
          *m_zeroContext,
          decoder(),
          m_nameForBackServer,
          radio_address,
          socket_address)) ;
  }
}

void THIS_CLASS::onReceiveConncetionMessage(const DataType& db,
    THIS_CLASS::NetConnectionType::pointer nc) {
  if(!nc) return ;

  if(isValidMessage(db, nc)) {
    if(needHeartBeat()) {
      nc->increaseHeartLevel() ;
    }
    dispatchConnectionMessage(db, nc) ;
  } else {
    pantheios::log_WARNING("msg not valid ", db) ;
    nc->onError() ;
  }
}

void THIS_CLASS::dispatchConnectionMessage(const DataType& db,
    THIS_CLASS::NetConnectionType::pointer nc) {
  if(!m_client_handlers.dispatch(db.messageType(), std::make_tuple(std::cref(db),
          nc))) {
    if(isRegisterConnection(nc) && isConnectedToBack())
      pushMessageToBack(db) ;
  }
}

void THIS_CLASS::pushMessageToBack(const DataType& db) const {
  pushCacheMessageToBack(makeCached(db)) ;
}

void THIS_CLASS::startReceiveConnection() {
  Utility::PageParser pp(m_propertyFile) ;
  // set accetpor for *NORMAL* player........
  m_port = pp.get(Net, ListenPort, 0);
  pantheios::log_DEBUG("we listen client port is ", pan::i(m_port)) ;
  PANTHEIOS_MESSAGE_ASSERT(m_port != 0,
      "we need ListenPort to cocumacate with client") ;

  m_hard_system_prepared_message_limit = pp.get(Net, HardPoolMessageSize, 10000L) ;
  m_ungentMaxSendSize = pp.get(Net, MaxSendUngentMessageSize, 100) ;
  m_normal_max_send_size = pp.get(Net, MaxSendNormalMessageSize, m_ungentMaxSendSize) ;
  auto handle_connect = boost::bind(&THIS_CLASS::onNewConnection, this, _1, _2) ;
  auto handle_connect_success = boost::bind(&THIS_CLASS::makeConnectionValid, this, _1) ;
  auto handle_error = boost::bind(&THIS_CLASS::onConnectionLeave, this, _1, _2);
  auto handle_data = boost::bind(&THIS_CLASS::onReceiveConncetionMessage, this, _1, _2) ;
  AcceptorType::NetAcceptorProperty prop(handle_connect,
      handle_connect_success,
      handle_error,
      handle_data) ;
  PANTHEIOS_ASSERT(m_readStrand);
  //PANTHEIOS_MESSAGE_ASSERT(m_readStrand.get_io_service(), "we need io_service....") ;
  m_acceptor = AcceptorType::create(
      *m_readStrand,
      *m_writeStrand,
      decoder(),
      m_port, prop) ;

  second_tt rate = second_tt(pp.get(ClientOption, HeartBeatRate, 0)) ;
  if(rate > 0) {
    decoder().registerBuilder<Server::Stock::HeartBeat>();
    m_maxAnswerTime=
      second_tt(pp.get(ClientOption, MaxAnswerTime, 0)) ;
    pan::log_DEBUG("heart beat rate : ", pan::i(rate.base_type_value()),
        " answer time is : ", pan::i(m_maxAnswerTime.base_type_value())) ;
    PANTHEIOS_MESSAGE_ASSERT(m_maxAnswerTime> rate,
        "we need right MaxAnswerTime") ;
    registerRepeatTimer(rate, boost::bind(&THIS_CLASS::dealHeartBeat, this)) ;
    m_client_handlers.add(Server::Stock::HeartBeat::value,
        [](MessageHandlerType){}) ;
  }

  registerRepeatTimer(second_tt(1), [this]() {
      Utility::LockGuard<decltype(m_delayActor)> guard(m_delayActor);
      m_delayActor.action() ;
      }) ;

  // start connect client
  m_acceptor->asyncConnect();
}

void THIS_CLASS::makeDecorderLocked() {
    decoder().makeFinal();
}

void THIS_CLASS::registerRepeatTimer(second_tt inteval,
    const NetCore::TimerEvent::CallBack& func) {
  m_timers.push_back(NetCore::TimerEvent::create(*m_readStrand,
        inteval,
        func
        )) ;
}

void THIS_CLASS::dealHeartBeat() {
  auto declevel = [](NetConnectionType::pointer nc) {
    nc->decreaseHeartLevel() ;
  } ;

  m_acceptor->processInplaceAction(std::move(declevel)) ;

  auto cond = [](NetConnectionType::pointer nc) -> bool {
    return nc->isHeartDead() ;
  } ;

  auto fun = [](NetConnectionType::pointer nc) { nc->onError() ;} ;
  m_acceptor->processAction(std::move(cond), std::move(fun)) ;

  auto needheart = [](NetConnectionType::pointer nc) -> bool {
    return nc->isNeedHeartBeat() ;
  } ;

  Stock::HeartBeat heart ;
  auto cache = Message::easyDataBlockCache(heart, player_tt(0)) ;

  auto sendnotify = [cache](NetConnectionType::pointer nc) {
    nc->sendAsyncMessage(cache) ;
  } ;

  m_acceptor->processAction(std::move(needheart), std::move(sendnotify)) ;
}


void
THIS_CLASS::makeConnectionValid(THIS_CLASS::NetConnectionType::pointer nc) {

  pan::log_DEBUG("start reseive player data....") ;
  nc->start() ;
  pan::log_DEBUG("real start ok....") ;
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
  if(isConnectedToBack()) {
    m_socket->bindPollManager(mgr,
        boost::bind(&THIS_CLASS::dealBackMessage,
          this,
          _1),
        boost::bind(&THIS_CLASS::dealBackRadioMessage,
          this,
          _1)
        ) ;
    mgr->registerWriteActor(std::bind(&THIS_CLASS::absorbDelaySystemMessage,
          this), ZPollInManager::OT_FRONT) ;
  }

  doBindPollManager(mgr) ;
}

void THIS_CLASS::sendFastMessage() {
  sendWaitingMessage(m_ungentMaxSendSize, m_ungentMessage);
}

void THIS_CLASS::sendWaitingMessage(size_t maxSendSize,
                                    UngentMessageGroup& messages) {
  size_t sendSize = std::min(maxSendSize, m_ungentMessage.size()) ;
  auto iter = messages.begin(), iter_end = messages.begin() + sendSize;
  std::for_each(iter, iter_end, [this](UngentMessageGroup::const_reference v) {
      dispatchBackServerMessage(v) ;
      }) ;
  messages.erase(iter, iter_end) ;
}

void THIS_CLASS::sendNormalMessage() {
  sendWaitingMessage(m_normal_max_send_size, m_waitingPostMessage);
}


void THIS_CLASS::absorbDelaySystemMessage() {
  if(m_ungentMessage.empty() && m_canDelayedMessage.empty() && m_waitingPostMessage.empty()) return ; // many times it is TRUE
  if(!m_ungentMessage.empty()) sendFastMessage() ;
  if(m_ungentMessage.empty() && !m_waitingPostMessage.empty()) sendNormalMessage() ;
  if(m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool()) {
  } else if(m_ungentMessage.empty() && m_waitingPostMessage.empty()) {
    while(!m_canDelayedMessage.empty()) {
      dispatchBackServerMessage(m_canDelayedMessage.front()) ;
      m_canDelayedMessage.pop_front() ;
      if(m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool()) break ;
    }
  }
}

void THIS_CLASS::handleBackInnerMessage(const DataType& db) {
  auto msg = db.constBody<Stock::InnerMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.importFromString(msg->information(), decoder()) ;
  PANTHEIOS_ASSERT(ok) ;
  PANTHEIOS_ASSERT(db2.messageType() != db.messageType()) ;
  db2.setHeaderId(db.headerId()) ;
  dispatchBackServerMessage(db2) ;
}

void THIS_CLASS::handleBackInnerPostMessage(const DataType& db) {
  auto msg = db.constBody<Stock::InnerPostMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.importFromString(msg->information(), decoder()) ;
  PANTHEIOS_ASSERT(ok) ;
  PlayerGroup ids ;
  for(int i = 0, size = msg->omitted_id_size() ; i < size ; ++i)
    ids.push_back(player_tt(msg->omitted_id(i))) ;
  if(msg->has_group()) {
    MiniGroup group(msg->group().id(),
        msg->group().type(),
        msg->group().property());
      doDealBackServerGroupMessage(group, db2, ids) ;
  } else {
    doDealBackServerPostMessage(db2, ids);
  }
}

void THIS_CLASS::dispatchBackServerMessage(const DataType& db) {
  if(!m_back_dealer_handlers.dispatch(db.messageType(), db)) {
    doDefaultBackMessageCallback(db) ;
  }
}

void THIS_CLASS::dispatchBackServerBroadcastMessage(const DataType& db) {
  if(!m_back_subscriber_dealers.dispatch(db.messageType(), db))
    sendMessageToAllConnection(db) ;
}

void THIS_CLASS::dealBackMessage(std::shared_ptr<DataType> d) {
  auto& db = *d;
  if(current_prepared_message_number_of_net_pool() > m_hard_system_prepared_message_limit ||
      !m_ungentMessage.empty()) {
    m_ungentMessage.push_back(db) ;
  } else {
    dispatchBackServerMessage(db) ;
  }
}

bool THIS_CLASS::isFasterPostMessage(const DataType& db) const {
  if(db.messageType() != Stock::InnerPostMessage::value) return false ;
  auto msg = db.constBody<Stock::InnerPostMessage>() ;
  return msg->no_delay() ;
}

bool THIS_CLASS::isTooManyMessageWaitingForDealing() const {
  return !m_ungentMessage.empty() || // has ungent message
    !m_waitingPostMessage.empty() || // has not send normal post message
    // or has two many message in poll to send
    m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool() ;

}

void THIS_CLASS::dealBackRadioMessage(std::shared_ptr<DataType> d) {
  auto& db = *d;
  auto hasWaitingMessage = isTooManyMessageWaitingForDealing() ;
  bool needdelay = hasWaitingMessage || !m_canDelayedMessage.empty() ;

  if(isNormalPostMessage(db.messageType()) ||
      isFasterPostMessage(db)) {
    if(hasWaitingMessage) {
      pantheios::log_DEBUG("make the message delay", pan::i(db.messageType())) ;
      m_waitingPostMessage.push_back(db) ;
    } else
      dispatchBackServerBroadcastMessage(db) ;
  } else if(needdelay) {
    m_canDelayedMessage.push_back(db) ;
  }
  else {
    dispatchBackServerBroadcastMessage(db) ;
  }
}

#undef THIS_CLASS
