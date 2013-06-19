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
  m_io_service(option.IoService),
  m_zeroContext(option.ZeroContext),
  m_readStrand(option.ReadStrand),
  m_writeStrand(option.WriteStrand),
  m_decoder(option.Decoder),
  m_socket(),
  m_init_file(option.PropertyFileName),
  m_client_handlers(),
  m_back_dealer_handlers(),
  m_back_subscriber_dealers(),
  m_acceptor(),
  m_timers(),
  m_registered_name(""),
  m_maxAnswerTime(0) ,
  m_hasBack(true),
  m_port(0),
  m_hard_system_prepared_message_limit(10000),
  m_delayActor(MaxDelayTime) {
  }

void THIS_CLASS::init() {
  initDecoder();
  connectBack() ;
  startReceiveConnection() ;
  initOtherService() ;
  registerStockMessage() ;
  registerActions() ;


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
  Utility::PageParser pp(m_init_file) ;

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
    m_registered_name=
      pp.get(Net, NameOfMyself, default_address) ;
    PANTHEIOS_MESSAGE_ASSERT(!m_registered_name.empty(),
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
          *m_decoder,
          m_registered_name,
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
  Utility::PageParser pp(m_init_file) ;
  // set accetpor for *NORMAL* player........
  m_port = pp.get(Net, ListenPort, 0);
  pantheios::log_DEBUG("we listen client port is ", pan::i(m_port)) ;
  PANTHEIOS_MESSAGE_ASSERT(m_port != 0,
      "we need ListenPort to cocumacate with client") ;

  m_hard_system_prepared_message_limit = pp.get(Net, HardPoolMessageSize, 10000L) ;
  m_ungent_max_send_size = pp.get(Net, MaxSendUngentMessageSize, 100) ;
  m_normal_max_send_size = pp.get(Net, MaxSendNormalMessageSize, m_ungent_max_send_size) ;
  auto handle_connect = boost::bind(&THIS_CLASS::onNewConnection, this, _1, _2) ;
  auto handle_connect_success = boost::bind(&THIS_CLASS::makeConnectionValid, this, _1) ;
  auto handle_error = boost::bind(&THIS_CLASS::onConnectionLeave, this, _1, _2);
  auto handle_data = boost::bind(&THIS_CLASS::onReceiveConncetionMessage, this, _1, _2) ;
  AcceptorType::NetAcceptorProperty prop(handle_connect,
      handle_connect_success,
      handle_error,
      handle_data) ;
  PANTHEIOS_MESSAGE_ASSERT(m_io_service, "we need io_service....") ;
  m_acceptor = AcceptorType::create(
      *m_readStrand,
      *m_writeStrand,
      *m_decoder,
      m_port, prop) ;

  second_tt rate = second_tt(pp.get(ClientOption, HeartBeatRate, 0)) ;
  if(rate > 0) {
    PANTHEIOS_ASSERT(m_decoder);
    m_decoder->registerBuilder<Server::Stock::HeartBeat>();
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
  if (m_decoder)
    m_decoder->makeFinal();
}

void THIS_CLASS::registerRepeatTimer(second_tt inteval,
    const NetCore::timer_event_function_type& func) {
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
  size_t max_send_size = std::min(m_ungent_max_send_size, m_ungent_message.size()) ;
  pan::log_DEBUG("send ungent msg ", pan::i(max_send_size), " ",
      pan::i(m_ungent_message.size())) ;
  auto iter = m_ungent_message.begin(), iter_end = m_ungent_message.begin() + max_send_size ;
  std::for_each(iter, iter_end, [this](UngentMessageGroup::const_reference v) {
      make_message_to_named_dealer(v) ;
      }) ;
  m_ungent_message.erase(iter, iter_end) ;
  pan::log_DEBUG("su ok") ;

}

void THIS_CLASS::postNormalMessage() {
  pantheios::log_DEBUG("Post Normal Message ", pan::i(m_normal_post_message.size())) ;
  size_t max_send_size = std::min(m_normal_max_send_size, m_normal_post_message.size()) ;
  auto iter = m_normal_post_message.begin(), iter_end = m_normal_post_message.begin() + max_send_size ;
  std::for_each(iter, iter_end, [this](NormalMessageGroup::const_reference v) {
      make_message_to_radio_dealer(v) ;
      }) ;
  m_normal_post_message.erase(iter, iter_end) ;
}

void THIS_CLASS::absorbDelaySystemMessage() {
  if(m_ungent_message.empty() && m_sys_delayed_message.empty() && m_normal_post_message.empty()) return ; // many times it is TRUE
  if(!m_ungent_message.empty()) sendFastMessage() ;
  if(m_ungent_message.empty() && !m_normal_post_message.empty()) postNormalMessage() ;
  if(m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool()) {
  } else if(m_ungent_message.empty() && m_normal_post_message.empty()) {
    while(!m_sys_delayed_message.empty()) {
      pan::log_DEBUG("call delayed..") ;
      make_message_to_radio_dealer(m_sys_delayed_message.front()) ;
      m_sys_delayed_message.pop_front() ;
      pan::log_DEBUG("cd ok") ;
      if(m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool()) break ;
    }

  }
}


void THIS_CLASS::handleBackInnerMessage(const DataType& db) {
  auto msg = db.constBody<Stock::InnerMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.importFromString(msg->information(), *m_decoder) ;
  PANTHEIOS_ASSERT(ok) ;
  PANTHEIOS_ASSERT(db2.messageType() != db.messageType()) ;
  db2.setHeaderId(db.headerId()) ;
  make_message_to_named_dealer(db2) ;
}

void THIS_CLASS::handleBackInnerPostMessage(const DataType& db) {
  auto msg = db.constBody<Stock::InnerPostMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.importFromString(msg->information(), *m_decoder) ;
  PANTHEIOS_ASSERT(ok) ;
  PlayerGroup ids ;
  for(int i = 0, size = msg->omitted_id_size() ; i < size ; ++i)
    ids.push_back(player_tt(msg->omitted_id(i))) ;
  if(msg->has_group()) {
    if(ids.empty()) {
      do_deal_back_post_message(msg->group().type(),
          msg->group().id(),msg->group().property(), db2) ;
    } else if(ids.size() == 1) {
      do_deal_back_post_message(msg->group().type(),
          msg->group().id(),
          msg->group().property(), db2, ids[0]) ;
    } else {
      do_deal_back_post_message(msg->group().type(),
          msg->group().id(),
          msg->group().property(), db2, ids) ;
    }
  } else {
    if(ids.empty()) sendMessageToAllConnection(db2) ;
    else if(ids.size() == 1)
      do_deal_back_post_message(db2, ids[0]) ;
    else do_deal_back_post_message(db2, ids) ;
  }
}

void THIS_CLASS::make_message_to_named_dealer(const DataType& db) {
  if(!m_back_dealer_handlers.dispatch(db.messageType(), db)) {
    doDefaultBackMessageCallback(db) ;
  }
}

void THIS_CLASS::make_message_to_radio_dealer(const DataType& db) {
  if(!m_back_subscriber_dealers.dispatch(db.messageType(), db))
    sendMessageToAllConnection(db) ;
}

void THIS_CLASS::dealBackMessage(std::shared_ptr<DataType> d) {
  auto& db = *d;
  if(current_prepared_message_number_of_net_pool() > m_hard_system_prepared_message_limit ||
      !m_ungent_message.empty()) {
    m_ungent_message.push_back(db) ;
  } else {
    make_message_to_named_dealer(db) ;
  }
}

bool THIS_CLASS::isFasterPostMessage(const DataType& db) const {
  if(db.messageType() != Stock::InnerPostMessage::value) return false ;
  auto msg = db.constBody<Stock::InnerPostMessage>() ;
  return msg->no_delay() ;
}

bool THIS_CLASS::isNormalMessageNeedDelay() const {
  return !m_ungent_message.empty() || // has ungent message
    !m_normal_post_message.empty() || // has not send normal post message
    // or has two many message in poll to send
    m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool() ;

}

void THIS_CLASS::dealBackRadioMessage(std::shared_ptr<DataType> d) {
  auto& db = *d;
  auto normalNeedDelay = isNormalMessageNeedDelay() ;
  bool needdelay = normalNeedDelay || !m_sys_delayed_message.empty() ;

  if(isNormalPostMessage(db.messageType()) ||
      isFasterPostMessage(db)) {
    if(normalNeedDelay) {
      pantheios::log_DEBUG("make the message delay", pan::i(db.messageType())) ;
      m_normal_post_message.push_back(db) ;
    } else make_message_to_radio_dealer(db) ;
  } else if(needdelay) m_sys_delayed_message.push_back(db) ;
  else make_message_to_radio_dealer(db) ;
}

#undef THIS_CLASS
