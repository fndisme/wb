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
#include <boost/noncopyable.hpp>
#ifndef WIN32
#include <folly/FBVector.h>
#endif
#include "webgame/netcore/DefaultNetConnectionDef.h"
#include "webgame/netcore/TimerEventFwd.h"
#include "webgame/utility/MessageManager.h"
#include "webgame/message/DataCache.h"
#include "webgame/server/ZSlaveServerSocket.h"
#include "webgame/message/MakeCacheMessage.h"
#include "webgame/shared/identity_type.h"
#include "webgame/shared/Platform.h"
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

    class DefaultZFrontServer : boost::noncopyable {
    public:
      typedef Message::DataBlock::DecoderType DecoderType;
      typedef ServerOption<Message::DataBlock::DecoderType> OptionType;
        void bindPollManager(ZPollInManager* mgr) ;
        void stop() ;
        void start() {
          doStart();
          makeDecorderLocked();
        }
      protected:
        virtual ~DefaultZFrontServer() NOEXCEPT;
        void init() ;
        DefaultZFrontServer(const OptionType& option) ;
        typedef Message::DataBlock DataType ;
        typedef NetCore::DefaultNetConnectType NetConnectionType ;
        typedef NetCore::MessageHandlerType MessageHandlerType;
        typedef std::shared_ptr<NetConnectionType> NetConnectionPointer ;
        typedef std::shared_ptr<const NetConnectionType> ConstNetConnectionPointer ;
        typedef NetCore::Acceptor<NetConnectionType> AcceptorType ;
        typedef boost::system::error_code NetErrorType ;
        bool onNewConnection(NetConnectionPointer, const NetErrorType&) {return true ;}
        bool needHeartBeat() const { return maxAnswerTime() != 0;}
        second_tt maxAnswerTime() const { return m_max_answer_time;}
        inline bool isRegisterConnection(NetConnectionPointer nc) const {
          return doIsRegisterConnection(nc) ;
        }
        DecoderType* decoder() { return m_decoder;}
        inline bool isNormalMessage(int msg) const {
          return m_normal_messages.find(msg) != m_normal_messages.end() ;
        }
        bool isNormalPostMessage(int msg) const {
          return m_normal_register_message.count(msg) == 1 ;
        }
        void registerNormalMessage(int msg) {
          m_normal_messages.insert(msg) ;
        }
        void registerNormalPostMessage(int msg) {
          m_normal_register_message.insert(msg) ;
        }

        bool isNormalMessageNeedDelay() const ;
        bool isFasterPostMessage(const DataType&) const ;
        inline bool isValidMessage(DataType const& db, NetConnectionPointer nc) const {
          return doIsValidMessage(db, nc) ;
        }
        virtual void makeConnectionValid(NetConnectionPointer);
        void onReceiveConncetionMessage(const DataType&, NetConnectionPointer)  ;
        inline void onConnectionLeave(const NetErrorType& error, NetConnectionPointer nc) {
          doOnConnectionLeave(error, nc) ;
        }
        inline void sendMessageToAllConnection(const DataType& db) const {
          doSendMessageToAllConnection(db) ;
        }
        int listenPort() const { return m_port ;}
        inline void registerActions() {
          doRegisterActions() ;
        }
        void makeMessageDealersFinal() {
          m_client_handlers.lock() ; // for client
          m_back_dealer_handlers.lock() ; // for back poster
          m_back_subscriber_dealers.lock() ; // for back radio
        }

        const std::string& propertyFileName() const { return m_init_file ;}
        typedef QSocketTratis::context_t ContextType ;
        ContextType* context() { return m_zero_ctx ;}

        typedef Utility::MessageManager<int, MessageHandlerType> MessageDealerType ;
        typedef Utility::MessageManager<int, DataType> BackMessageDealerType ;
#ifdef WIN32
        typedef std::vector<player_tt> PlayerGroup;
#else
        typedef folly::fbvector<player_tt> PlayerGroup ;
#endif
        void registerConnectionMessageCallback(int k, MessageDealerType::function_type const& func) {
          registerNormalMessage(k) ;
          m_client_handlers.add(k, func) ;
        }

        void registerBackMessageCallback(int k, BackMessageDealerType::function_type const& func) {
          m_back_dealer_handlers.add(k, func) ;
        }

        void registerBackRedioMessageCallback(int k, BackMessageDealerType::function_type const& func) {
          m_back_subscriber_dealers.add(k, func) ;
        }
        void pushMessageToBack(const DataType& db) const ;
        void pushCacheMessageToBack(Message::DataCache::const_pointer cache) const {
          m_socket->sendMessage(cache) ;
        }

        void registerRepeatTimer(second_tt inteval, const NetCore::timer_event_function_type& fun) ;

        template<typename MSG>
          void pushMessageToBack(MSG&& msg, player_tt pid = player_tt(0)) const {
            pushCacheMessageToBack(easy_data_block_cache(std::forward<MSG>(msg), pid)) ;
          }

        const std::string& name() const { return m_registered_name ;}

#ifdef WIN32
        typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
        typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
        typedef ZSlaveServerSocket<Message::DataCache::const_pointer, DataType, SocketDataVector> ZSocketType ;
      protected:
        template<typename Action>
          void addDelayAction(size_t position, Action&& act) {
            m_delay_actor.addAction(position, std::forward<Action>(act)) ;
          }
      private:
        boost::asio::io_service* m_io_service ;
        ContextType* m_zero_ctx ;
        boost::asio::strand* m_readStrand;
        boost::asio::strand* m_writeStrand;
        DecoderType* m_decoder;
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
        void dealHeartBeat() ;
        void makeDecorderLocked();
        void dealBackMessage(std::shared_ptr<DataType> db) ;
        void dealBackRadioMessage(std::shared_ptr<DataType> db) ;
        void connectBack() ;
        void initDecoder() { doInitDecoder();}
        void startReceiveConnection() ;
        void dispatchConnectionMessage(const DataType&, NetConnectionPointer)  ;
        void registerStockMessage() ;
        void handleBackInnerMessage(const DataType&) ;
        void handleBackInnerPostMessage(const DataType&) ;
        void initOtherService() { doInitOtherService() ;}

        virtual void doDefaultBackMessageCallback(const DataType&) const = 0;
        virtual void doSendMessageToAllConnection(const DataType& db) const = 0 ;
        virtual void doOnConnectionLeave(const NetErrorType&, NetConnectionPointer) = 0 ;
        virtual bool doIsValidMessage(const DataType& db, NetConnectionPointer nc) const = 0 ;
        virtual bool doIsRegisterConnection(NetConnectionPointer nc) const = 0 ;
        virtual void doRegisterActions() = 0 ;
        virtual void do_deal_back_post_message(const DataType& db, PlayerGroup const&) = 0 ;
        virtual void do_deal_back_post_message(const DataType& db, player_tt pid) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db, PlayerGroup const&) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db, player_tt pid) = 0 ;
        virtual void do_deal_back_post_message(int, int, int,const DataType& db) = 0 ;
        virtual void doInitOtherService() {} // do nothing default
        virtual void doBindPollManager(ZPollInManager* /*mgr*/) {} // normal we do nothing for bind poll mgr
        virtual void doStart() { init();}
        virtual void doInitDecoder() = 0;
        second_tt m_max_answer_time ;

        bool m_has_back ;
        bool isConnectedToBack() const { return m_has_back ;}
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
        void sendFastMessage() ;
        size_t m_hard_system_prepared_message_limit ;
        void absorbDelaySystemMessage() ;
        void make_message_to_named_dealer(const DataType&) ;
        void make_message_to_radio_dealer(const DataType&) ;
        size_t m_ungent_max_send_size ;
        void postNormalMessage() ;
        size_t m_normal_max_send_size ;

        typedef Utility::CircleActor<Utility::DelayMessageDealer> DelayMessageActor ;

        DelayMessageActor m_delay_actor ;

        enum { MaxDelayTime = 10 } ;
    } ;
  }
}
#endif
