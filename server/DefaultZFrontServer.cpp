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
#include "webgame/server/ZPollInManager.h"
#include "webgame/utility/PageParser.h"

// base message
#include "webgame/message/HeartBeat.pb.h"
#include "webgame/message/InnerMessage.pb.h"
#include "webgame/message/InnerPostMessage.pb.h"

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


void THIS_CLASS::handle_HeartBeat(WebGame::MessageHandlerType /*  param */) {
}



THIS_CLASS::~DefaultZFrontServer() noexcept {}

void THIS_CLASS::stop() {
  m_acceptor->stop_all() ;
}

THIS_CLASS::DefaultZFrontServer(const ServerOption& option) :
  m_io_service(option.IoService),
  m_zero_ctx(option.ZeroContext),
  m_socket{},
  m_init_file(option.PropertyFileName),
  m_client_handlers{},
  m_back_dealer_handlers{},
  m_back_subscriber_dealers{},
  m_acceptor{},
  m_timers{},
  m_registered_name(""),
  m_normal_messages{},
  m_max_answer_time(0) ,
  //m_flow_controler(new FlowControlerType),
  m_has_back(true),
  m_port(0),
  m_hard_system_prepared_message_limit(10000),
  m_delay_actor(MaxDelayTime){
    //init() ;
  }

void THIS_CLASS::init() {
  connect_to_back() ;
  give_service_to_customers() ;

  init_other_service() ;

  register_stock_actions() ;
  register_actions() ;


  make_message_dealers_final() ;
  
}

void THIS_CLASS::register_stock_actions() {
  if(m_has_back) {
    m_back_dealer_handlers.add(game_connection::InnerMessage::value,
        boost::bind(&THIS_CLASS::handle_Back_InnerMessage,
          this,
          _1)) ;

    m_back_subscriber_dealers.add(game_connection::InnerPostMessage::value,
        boost::bind(&THIS_CLASS::handle_Back_InnerPostMessage,
          this,
          _1)) ;
  }

  if(need_heart_beat()) m_normal_messages.insert(game_connection::HeartBeat::value) ;
}

void THIS_CLASS::connect_to_back() {
	Utility::page_parser pp(m_init_file) ;

  m_has_back = pp.get(Net, IsHasBackServer, 1) > 0 ;

  if(m_has_back) {
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

  PANTHEIOS_ASSERT(m_zero_ctx) ;

  m_socket.reset(new ZSocketType(*m_zero_ctx, m_registered_name, radio_address,
        socket_address)) ;
  }
}

void THIS_CLASS::receive_customer_message(const DataType& db,
    THIS_CLASS::NetConnectionType::pointer nc) {
  if(!nc) return ;

  if(is_valid_message(db, nc)) {
    if(need_heart_beat()) {
      nc->increase_heart_level() ;
    }
    deal_client_message(db, nc) ;
  } else {
    pantheios::log_WARNING("msg not valid ", db) ;
    nc->on_error() ;
  }
}


void THIS_CLASS::deal_client_message(const DataType& db,
		THIS_CLASS::NetConnectionType::pointer nc) {
	if(!m_client_handlers.deal_with_message(db.message_type(), std::make_tuple(std::cref(db),
					nc))) {
		if(is_register_client(nc) && has_back_server())
			push_message_to_back(db) ;
	}
}

void THIS_CLASS::push_message_to_back(const DataType& db) const {
  push_cache_message_to_back(make_cached(db)) ;
}

WebGame::second_tt THIS_CLASS::max_answer_time() const {
  return m_max_answer_time ;
}

void THIS_CLASS::give_service_to_customers() {
  Utility::page_parser pp(m_init_file) ;
  // set accetpor for *NORMAL* player........
  m_port = pp.get(Net, ListenPort, 0);
  pantheios::log_DEBUG("we listen client port is ", pan::i(m_port)) ;
  PANTHEIOS_MESSAGE_ASSERT(m_port != 0,
      "we need ListenPort to cocumacate with client") ;

  m_hard_system_prepared_message_limit = pp.get(Net, HardPoolMessageSize, 10000L) ;
  m_ungent_max_send_size = pp.get(Net, MaxSendUngentMessageSize, 100) ;
  m_normal_max_send_size = pp.get(Net, MaxSendNormalMessageSize, m_ungent_max_send_size) ;

  auto handle_connect = boost::bind(&THIS_CLASS::handle_customer_enter, this, _1, _2) ;
  auto handle_connect_success = boost::bind(&THIS_CLASS::handle_customer_award_a_contract, this, _1) ;
  auto handle_error = boost::bind(&THIS_CLASS::handle_customer_leave, this, _1, _2);
  auto handle_data = boost::bind(&THIS_CLASS::receive_customer_message, this, _1, _2) ;
  AcceptorType::NetAcceptorProperty prop(handle_connect,
      handle_connect_success,
      handle_error,
      handle_data) ;
  PANTHEIOS_MESSAGE_ASSERT(m_io_service, "we need io_service....") ;
  m_acceptor = AcceptorType::create_net_acceptor(*m_io_service,
      m_port, prop) ;


  second_tt rate = second_tt(pp.get(ClientOption, HeartBeatRate, 0)) ;
    if(rate > 0) {
    m_max_answer_time =
      second_tt(pp.get(ClientOption, MaxAnswerTime, 0)) ;
    pan::log_DEBUG("heart beat rate : ", pan::i(rate.base_type_value()),
      " answer time is : ", pan::i(m_max_answer_time.base_type_value())) ;

    PANTHEIOS_MESSAGE_ASSERT(m_max_answer_time > rate,
        "we need right MaxAnswerTime") ;

    register_repeat_timer(rate, boost::bind(&THIS_CLASS::handle_client_heart_beat, this)) ;

    m_client_handlers.add(game_connection::HeartBeat::value,
        boost::bind(&THIS_CLASS::handle_HeartBeat,
          this,
          _1)) ;
  }
  
  register_repeat_timer(second_tt(1), [this]() {
      m_delay_actor.lock() ;
      m_delay_actor.action() ;
      m_delay_actor.unlock() ;
      }) ;

  // start connect client
  m_acceptor->async_connect_a_client();
}

void THIS_CLASS::register_repeat_timer(second_tt inteval, 
    const timer_event_function_type& func) {
  m_timers.push_back(timer_event::create_timer_event(*m_io_service,
          inteval,
          func
          )) ;
}

void THIS_CLASS::handle_client_heart_beat() {
  auto declevel = [](NetConnectionType::pointer nc) {
    nc->decrease_heart_level() ;
  } ;

  m_acceptor->process_inplace_event(std::move(declevel)) ;

	auto cond = [](NetConnectionType::pointer nc) -> bool {
		return nc->is_heart_dead() ;
	} ;

	auto fun = [](NetConnectionType::pointer nc) { nc->on_error() ;} ;
	m_acceptor->process_event_for_connections(std::move(cond), std::move(fun)) ;

  auto needheart = [](NetConnectionType::pointer nc) -> bool {
    return nc->is_need_send_heart_beat() ;
  } ;

  game_connection::HeartBeat heart ;
  heart.set_dummy(1) ;
  auto cache = easy_data_block_cache(heart, player_tt(0)) ;

  auto sendnotify = [cache](NetConnectionType::pointer nc) {
    nc->send_async_message(cache) ;
  } ;

  m_acceptor->process_event_for_connections(std::move(needheart), std::move(sendnotify)) ;
}


void
THIS_CLASS::handle_customer_award_a_contract(THIS_CLASS::NetConnectionType::pointer nc) {

  pan::log_DEBUG("start reseive player data....") ;
	nc->start() ;
  pan::log_DEBUG("real start ok....") ;
}

void THIS_CLASS::bind_to_poll_manager(WebGame::ZPollInManager* mgr) {
  if(has_back_server()) {
  m_socket->bind_to_poll_manager(mgr,
      boost::bind(&THIS_CLASS::deal_message_from_back_poster,
        this,
        _1),
      boost::bind(&THIS_CLASS::deal_message_from_back_radio,
        this,
        _1)
      ) ;
  mgr->register_absolute_actor(std::bind(&THIS_CLASS::absorb_delayed_system_message,
        this), ZPollInManager::OT_FRONT) ;
//  mgr->register_absolute_actor(std::bind(&THIS_CLASS::set_delay_flags,
//        this), ZPollInManager::OT_FRONT) ;
//  mgr->register_absolute_actor(std::bind(&THIS_CLASS::absorb_delayed_system_message,
//        this)) ;
  }

//  mgr->register_absolute_actor(std::bind(&THIS_CLASS::send_delay_flow_message,
//        this)) ;
//
  do_bind_to_poll_manager(mgr) ;
}

void THIS_CLASS::send_ungent_message() {
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

void THIS_CLASS::post_normal_message() {
  pantheios::log_DEBUG("Post Normal Message ", pan::i(m_normal_post_message.size())) ;
size_t max_send_size = std::min(m_normal_max_send_size, m_normal_post_message.size()) ;
  auto iter = m_normal_post_message.begin(), iter_end = m_normal_post_message.begin() + max_send_size ;
  std::for_each(iter, iter_end, [this](NormalMessageGroup::const_reference v) {
      make_message_to_radio_dealer(v) ;
      }) ;
  m_normal_post_message.erase(iter, iter_end) ;
}

void THIS_CLASS::absorb_delayed_system_message() {
  if(m_ungent_message.empty() && m_sys_delayed_message.empty() && m_normal_post_message.empty()) return ; // many times it is TRUE
  if(!m_ungent_message.empty()) send_ungent_message() ;
  if(m_ungent_message.empty() && !m_normal_post_message.empty()) post_normal_message() ;
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

void THIS_CLASS::send_delay_flow_message() {
  //m_flow_controler->poll() ;
}

void THIS_CLASS::set_delay_flags() {
  //m_flow_controler->net_loose() ;
  //if(m_socket->is_busy()) m_flow_controler->net_busy() ;
  //else m_flow_controler->net_loose() ;
}

void THIS_CLASS::handle_Back_InnerMessage(const DataType& db) {
  auto msg = db.const_body<game_connection::InnerMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.import_from_string(msg->information()) ;
  PANTHEIOS_ASSERT(ok) ;
  PANTHEIOS_ASSERT(db2.message_type() != db.message_type()) ;
  db2.set_header_id(db.header_id()) ;
  make_message_to_named_dealer(db2) ;
}

void THIS_CLASS::handle_Back_InnerPostMessage(const DataType& db) {
  auto msg = db.const_body<game_connection::InnerPostMessage>() ;
  PANTHEIOS_ASSERT(msg) ;
  DataType db2 ;
  bool ok = db2.import_from_string(msg->information()) ;
  PANTHEIOS_ASSERT(ok) ;
  PlayerGroup ids ;
  for(int i = 0, size = msg->omitted_id_size() ; i < size ; ++i)
    ids.push_back(player_tt(msg->omitted_id(i))) ;
  if(msg->has_group()) {
    if(ids.empty()) {
      do_deal_back_post_message(msg->group().type(),
                                msg->group().group_id(),msg->group().group_property(), db2) ;
    } else if(ids.size() == 1) {
      do_deal_back_post_message(msg->group().type(),
                                msg->group().group_id(),
                                msg->group().group_property(), db2, ids[0]) ;
    } else {
    do_deal_back_post_message(msg->group().type(),
                              msg->group().group_id(),
                              msg->group().group_property(), db2, ids) ;
    }
  } else {
    if(ids.empty()) send_message_to_all_client(db2) ;
    else if(ids.size() == 1)
      do_deal_back_post_message(db2, ids[0]) ;
    else do_deal_back_post_message(db2, ids) ;
  }
}

void THIS_CLASS::make_message_to_named_dealer(const DataType& db) {
if(!m_back_dealer_handlers.deal_with_message(db.message_type(), std::cref(db))) {
    do_default_deal_back_message(db) ;
  }
}

void THIS_CLASS::make_message_to_radio_dealer(const DataType& db) {
if(!m_back_subscriber_dealers.deal_with_message(db.message_type(), std::cref(db)))
    send_message_to_all_client(db) ;
}

void THIS_CLASS::deal_message_from_back_poster(const DataType& db) {
  pantheios::log_DEBUG("dm: ", db) ;
  if(current_prepared_message_number_of_net_pool() > m_hard_system_prepared_message_limit ||
      !m_ungent_message.empty()) {
    m_ungent_message.push_back(db) ;
  } else {
    make_message_to_named_dealer(db) ;
  }
  pantheios::log_DEBUG("dok") ;
}

bool THIS_CLASS::is_normal_post_message(int msg) const {
  return m_normal_register_message.count(msg) == 1 ;
}

bool THIS_CLASS::is_no_delayed_inner_post_message(const DataType& db) const {
  if(db.message_type() != game_connection::InnerPostMessage::value) return false ;
  auto msg = db.const_body<game_connection::InnerPostMessage>() ;
  return msg->no_delay() ;
}

bool THIS_CLASS::is_normal_message_need_delay() const {
  return !m_ungent_message.empty() || // has ungent message
    !m_normal_post_message.empty() || // has not send normal post message
    // or has two many message in poll to send
    m_hard_system_prepared_message_limit < current_prepared_message_number_of_net_pool() ;

}

void THIS_CLASS::deal_message_from_back_radio(const DataType& db) {
  pantheios::log_DEBUG("dr: ", db) ;
  auto normalNeedDelay = is_normal_message_need_delay() ;
  bool needdelay = normalNeedDelay || !m_sys_delayed_message.empty() ;

  if(is_normal_post_message(db.message_type()) ||
      is_no_delayed_inner_post_message(db)) {
    if(normalNeedDelay) {
      pantheios::log_DEBUG("make the message delay", pan::i(db.message_type())) ;
      m_normal_post_message.push_back(db) ;
    } else make_message_to_radio_dealer(db) ;
  } else if(needdelay) m_sys_delayed_message.push_back(db) ;
  else make_message_to_radio_dealer(db) ;
  pan::log_DEBUG("dro") ;
}

#undef THIS_CLASS
