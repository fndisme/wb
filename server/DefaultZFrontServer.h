/*
 * =====================================================================================
 *
 *       Filename:  DefaultZFrontServer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年03月06日 14时47分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_DEFAULT_ZFRONTSERVER_H
#define FND_WEBGAME_DEFAULT_ZFRONTSERVER_H
#include <memory>
#include <string>
#include <vector>
#include <boost/container/flat_set.hpp>
#include <boost/container/deque.hpp>
#include <folly/FBVector.h>
#include "webgame/netcore/DefaultNetConnectionDef.h"
#include "webgame/netcore/TimerEventFwd.h"
#include "webgame/utility/MessageManager.h"
#include "webgame/message/DataCache.h"
#include "webgame/server/ZSlaveServerSocket.h"
#include "webgame/message/MakeCacheMessage.h"
#include "webgame/shared/identity_type.h"
#include "webgame/utility/CircleActor.h"
#include "webgame/utility/DelayMessageDealer.h"
#include "webgame/server/ServerOption.h"


namespace boost {
  namespace system {
    class error_code ;
  }
}
namespace WebGame {
  namespace NetCore {
    template<typename Conn>
      class Acceptor;
  }
  namespace Server {
    class ZPollInManager ;

    //template<typename NetConnection> class FlowControler ;
    class DefaultZFrontServer {

      protected:

        virtual ~DefaultZFrontServer() noexcept ;
        void init() ;
        DefaultZFrontServer(const ServerOption& option) ;
        DefaultZFrontServer(DefaultZFrontServer const&) = delete ;
        DefaultZFrontServer& operator = (DefaultZFrontServer const&) = delete ;

      public:
        void bind_to_poll_manager(ZPollInManager* mgr) ;
        void stop() ;

      protected:
        typedef Message::DataBlock DataType ;
        typedef NetCore::DefaultNetConnectType NetConnectionType ;
        typedef NetCore::MessageHandlerType MessageHandlerType;
        typedef std::shared_ptr<NetConnectionType> NetConnectionPointer ;
        typedef std::shared_ptr<const NetConnectionType> ConstNetConnectionPointer ;
        typedef NetCore::Acceptor<NetConnectionType> AcceptorType ;
        typedef boost::system::error_code NetErrorType ;
        // typedef FlowControler<NetConnectionType> FlowControlerType ;
        // interface
        bool handle_customer_enter(NetConnectionPointer, const NetErrorType&) {return true ;}
        bool need_heart_beat() const { return max_answer_time() != 0;}
        second_tt max_answer_time() const ;
        inline bool is_register_client(NetConnectionPointer nc) const {
          return do_is_register_client(nc) ;
        }
        inline bool is_normal_client_message(int msg) const {
          return m_normal_messages.find(msg) != m_normal_messages.end() ;
        }
        bool is_normal_post_message(int msg) const ;
        void register_message_as_normal_client_message(int msg) {
          m_normal_messages.insert(msg) ;
        }
        void register_message_as_normal_post_message(int msg) {
          m_normal_register_message.insert(msg) ;
        }

        bool is_normal_message_need_delay() const ;
        bool is_no_delayed_inner_post_message(const DataType&) const ;
        inline bool is_valid_message(DataType const& db, NetConnectionPointer nc) const {
          return do_is_valid_message(db, nc) ;
        }
        virtual void handle_customer_award_a_contract(NetConnectionPointer)  ;
        void receive_customer_message(const DataType&, NetConnectionPointer)  ;
        inline void handle_customer_leave(const NetErrorType& error, NetConnectionPointer nc) {
          do_handle_customer_leave(error, nc) ;
        }
        inline void send_message_to_all_client(const DataType& db) const {
          do_send_message_to_all_client(db) ;
        }
        int listen_port() const { return m_port ;}
        inline void register_actions() {
          do_register_actions() ;
        }
        void make_message_dealers_final() {
          m_client_handlers.lock() ; // for client
          m_back_dealer_handlers.lock() ; // for back poster
          m_back_subscriber_dealers.lock() ; // for back radio
        }

        const std::string& property_file_name() const { return m_init_file ;}
        typedef QSocketTratis::context_t ContextType ;
        ContextType* context() { return m_zero_ctx ;}

        typedef Utility::MessageManager<int, MessageHandlerType> MessageDealerType ;
        typedef Utility::MessageManager<int, DataType> BackMessageDealerType ;
        typedef folly::fbvector<player_tt> PlayerGroup ;
        void register_client_message_handler(int k, MessageDealerType::function_type const& func) {
          register_message_as_normal_client_message(k) ;
          m_client_handlers.add(k, func) ;
        }

        void register_back_poster_message_handler(int k, BackMessageDealerType::function_type const& func) {
          m_back_dealer_handlers.add(k, func) ;
        }

        void register_back_radio_message_handler(int k, BackMessageDealerType::function_type const& func) {
          m_back_subscriber_dealers.add(k, func) ;
        }
        void push_message_to_back(const DataType& db) const ;
        void push_cache_message_to_back(Message::DataCache::const_pointer cache) const {
          m_socket->sendMessage(cache) ;
        }

        void register_repeat_timer(second_tt inteval, const NetCore::timer_event_function_type& fun) ;

        template<typename MSG>
          void push_message_to_back(MSG&& msg, player_tt pid = player_tt(0)) const {
            push_cache_message_to_back(easy_data_block_cache(std::forward<MSG>(msg), pid)) ;
          }

        const std::string& name() const { return m_registered_name ;}

        typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
        typedef ZSlaveServerSocket<Message::DataCache::const_pointer, DataType, SocketDataVector> ZSocketType ; 
      protected:
        template<typename Action>
          void add_delay_action(size_t position, Action&& act) {
            m_delay_actor.addAction(position, std::forward<Action>(act)) ;
          }
      private:
        boost::asio::io_service* m_io_service ;
        ContextType* m_zero_ctx ;
        std::unique_ptr<ZSocketType> m_socket ;
        const std::string m_init_file ;
        // handle message from client....
        MessageDealerType m_client_handlers ;
        BackMessageDealerType m_back_dealer_handlers ;
        BackMessageDealerType m_back_subscriber_dealers ;
        typedef std::unique_ptr<AcceptorType> AcceptorPointer ;
        AcceptorPointer m_acceptor ;

        std::vector<NetCore::timer_event_pointer> m_timers ;
        std::string m_registered_name ;
        boost::container::flat_set<int> m_normal_messages ;
        boost::container::flat_set<int> m_normal_register_message ;
        void handle_client_heart_beat() ;

        void deal_message_from_back_poster(const DataType& db) ;
        void deal_message_from_back_radio(const DataType& db) ;
        void handle_HeartBeat(MessageHandlerType param) ;
        void connect_to_back() ;
        void give_service_to_customers() ;
        void deal_client_message(const DataType&, NetConnectionPointer)  ;
        void register_stock_actions() ;
        void handle_Back_InnerMessage(const DataType&) ;
        void handle_Back_InnerPostMessage(const DataType&) ;
        void init_other_service() { do_init_other_service() ;}


        virtual void do_default_deal_back_message(const DataType&) const = 0;
        virtual void do_send_message_to_all_client(const DataType& db) const = 0 ; 
        virtual void do_handle_customer_leave(const NetErrorType&, NetConnectionPointer) = 0 ; 
        virtual bool do_is_valid_message(const DataType& db, NetConnectionPointer nc) const = 0 ;
        virtual bool do_is_register_client(NetConnectionPointer nc) const = 0 ;
        virtual void do_register_actions() = 0 ;
        virtual void do_deal_back_post_message(const DataType& db, PlayerGroup const&) = 0 ;
        virtual void do_deal_back_post_message(const DataType& db, player_tt pid) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db, PlayerGroup const&) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db, player_tt pid) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db) = 0 ;
        virtual void do_init_other_service() {} // do nothing default
        virtual void do_bind_to_poll_manager(ZPollInManager* /*mgr*/) {} // normal we do nothing for bind poll mgr
        second_tt m_max_answer_time ;

        // about flow control 
        // make some message delay to send client
        //mutable std::unique_ptr<FlowControlerType> m_flow_controler ;
        void send_delay_flow_message() ;
        void set_delay_flags() ;
        bool m_has_back ;
        bool has_back_server() const { return m_has_back ;}
        int m_port ;

        enum BackServerMessageType {
          BSM_RADIO,
          BSM_NAMED,
        } ;

        //typedef std::tuple<BackServerMessageType, DataType> HardCoreDelayedMessage ;

        typedef boost::container::deque<DataType> UngentMessageGroup ;
        typedef UngentMessageGroup HardCoreDelayedMessageGroup ;
        HardCoreDelayedMessageGroup m_sys_delayed_message ;
        UngentMessageGroup m_ungent_message ;
        typedef UngentMessageGroup NormalMessageGroup ;
        NormalMessageGroup m_normal_post_message ;
        void send_ungent_message() ;
        size_t m_hard_system_prepared_message_limit ;
        void absorb_delayed_system_message() ;
        void make_message_to_named_dealer(const DataType&) ;
        void make_message_to_radio_dealer(const DataType&) ;
        size_t m_ungent_max_send_size ;
        void post_normal_message() ;
        size_t m_normal_max_send_size ;

        typedef Utility::CircleActor<Utility::DelayMessageDealer> DelayMessageActor ;

        DelayMessageActor m_delay_actor ;

        enum { MaxDelayTime = 10 } ;
    } ;
  }
}
#endif
