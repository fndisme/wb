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
#include "webgame/server/ClientSet.h"
#include "webgame/server/FrontClientStub.h"

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
    struct ServerOption;
    class DefaultZFrontServer : boost::noncopyable {
    public:
      typedef Message::DataBlock::DecoderType DecoderType;
      typedef NetCore::DefaultNetConnectType NetConnectionType ;
      typedef std::shared_ptr<NetConnectionType> NetConnectionPointer ;
      typedef ServerOption OptionType;
        void bindPollManager(ZPollInManager* mgr) ;
        void stop() ;
        void start() {
          doStart();
          makeDecorderLocked();
        }
      protected:
        virtual ~DefaultZFrontServer() NOEXCEPT;
        void init() ;
        explicit DefaultZFrontServer(const OptionType& option);
        typedef Message::DataBlock DataType;
        typedef NetCore::MessageHandlerType MessageHandlerType;
        typedef std::shared_ptr<const NetConnectionType> ConstNetConnectionPointer ;
        typedef NetCore::Acceptor<NetConnectionType> AcceptorType ;
        typedef boost::system::error_code NetErrorType ;
        bool onNewConnection(NetConnectionPointer, const NetErrorType&) {return true ;}
        bool needHeartBeat() const { return maxAnswerTime() != 0;}
        second_tt maxAnswerTime() const { return m_maxAnswerTime;}
        inline bool isRegisterConnection(NetConnectionPointer nc) const {
          return doIsRegisterConnection(nc) ;
        }
        DecoderType& decoder() { return *m_decoder;}
        const DecoderType& decoder() const { return *m_decoder;}
        bool isNormalPostMessage(int msg) const {
          return m_normal_register_message.count(msg) == 1 ;
        }
        void registerNormalPostMessage(int msg) {
          m_normal_register_message.insert(msg) ;
        }

        bool isTooManyMessageWaitingForDealing() const ;
        bool isFasterPostMessage(const DataType&) const ;
        inline bool isValidMessage(DataType const& db,
                                   NetConnectionPointer nc) const {
          return doIsValidMessage(db, nc) ;
        }
        /**
         * @brief when client connection is successed connect to server. call
         * it, default action is make it read and write.
         *
         * @param NetConnectionPointer
         */
        void makeConnectionValid(NetConnectionPointer);
        void onReceiveConncetionMessage(const DataType&, NetConnectionPointer)  ;
        inline void onConnectionLeave(const NetErrorType& error,
                                      NetConnectionPointer nc) {
          removePlayerFromPlayerSet(nc);
          doOnConnectionLeave(error, nc) ;
        }
        inline void sendMessageToAllConnection(const DataType& db) const {
          doSendMessageToAllConnection(db) ;
        }
      private:
        short m_port;
      public:
        short listenPort() const { return m_port ;}
        inline void registerActions() {
          doRegisterActions() ;
        }
        void makeMessageDealersFinal() {
          m_clientMessageHandlers.lock() ; // for client
          m_back_dealer_handlers.lock() ; // for back poster
          m_back_subscriber_dealers.lock() ; // for back radio
        }

        const std::string& propertyFileName() const { return m_propertyFile;}
        typedef QSocketTraits::context_t ContextType ;
        ContextType* context() { return m_zeroContext;}

        typedef Utility::MessageManager<int, MessageHandlerType> MessageDealerType ;
        typedef Utility::MessageManager<int, DataType> BackMessageDealerType ;
#ifdef WIN32
        typedef std::vector<player_tt> PlayerGroup;
#else
        typedef folly::fbvector<player_tt> PlayerGroup ;
#endif
        void registerConnectionMessageCallback(int k,
            MessageDealerType::function_type const& func) {
          m_clientMessageHandlers.add(k, func) ;
        }

        void registerBackMessageCallback(int k,
            BackMessageDealerType::function_type const& func) {
          m_back_dealer_handlers.add(k, func) ;
        }

        void registerBackRedioMessageCallback(int k,
            BackMessageDealerType::function_type const& func) {
          m_back_subscriber_dealers.add(k, func) ;
        }
        void pushMessageToBack(const DataType& db) const ;
        void pushCacheMessageToBack(Message::DataCache::const_pointer cache) const {
          m_socket->sendMessage(cache) ;
        }

        void registerRepeatTimer(second_tt inteval,
            const NetCore::TimerEventCallBack& fun) ;

        template<typename MSG>
          void pushMessageToBack(MSG&& msg, player_tt pid = player_tt(0)) const {
            pushCacheMessageToBack(easy_data_block_cache(std::forward<MSG>(msg), pid)) ;
          }

        const std::string& name() const { return m_nameForBackServer;}

#ifdef WIN32
        typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
        typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
        typedef ZSlaveServerSocket<Message::DataCache::const_pointer,
                DataType, SocketDataVector> ZSocketType;
      protected:
        template<typename Action>
          void addDelayAction(size_t position, Action&& act) {
            m_delayActor.addAction(position, std::forward<Action>(act)) ;
          }
        struct MiniGroup {
          int Id;
          int Type;
          int Property;
          explicit MiniGroup(int id, int type, int property) :
            Id(id),
            Type(type),
            Property(property) {}
        };
      private:
        ContextType* m_zeroContext;
        typedef boost::asio::strand Strand;
        Strand* m_readStrand;
        Strand* m_writeStrand;
        std::unique_ptr<DecoderType> m_decoder;
        std::unique_ptr<ZSocketType> m_socket ;
        const std::string m_propertyFile;
        // handle message from client....
        MessageDealerType m_clientMessageHandlers ;
        BackMessageDealerType m_back_dealer_handlers ;
        BackMessageDealerType m_back_subscriber_dealers ;
        typedef std::unique_ptr<AcceptorType> AcceptorPointer ;
        AcceptorPointer m_acceptor ;

        std::vector<NetCore::TimerEventPonter> m_timers ;
        std::string m_nameForBackServer;
        boost::container::flat_set<int> m_normal_register_message ;
        void dealHeartBeat() ;
        void makeDecorderLocked();
        void dealBackMessage(std::shared_ptr<DataType> db) ;
        void dealBackRadioMessage(std::shared_ptr<DataType> db) ;
        void connectBack() ;
        void startReceiveConnection() ;
        void dispatchConnectionMessage(const DataType&, NetConnectionPointer)  ;
        void registerStockMessage() ;
        void handleBackInnerMessage(const DataType&) ;
        void handleBackInnerPostMessage(const DataType&) ;
        void initOtherService() { doInitOtherService() ;}

        /// after are child class must instanced
        /**
         * @brief when the server could not deal the message. call it.
         *
         * @param DataType the message back send to front
         */
        virtual void doDefaultBackMessageCallback(const DataType&) const = 0;
        virtual void doMakeConnectionValid(NetConnectionPointer nc) {}
        /**
         * @brief send message to all client.
         *
         * @param db message
         */
        virtual void doSendMessageToAllConnection(const DataType& db) const = 0 ;
        /**
         * @brief when client socket disconnected call it
         *
         * @param NetErrorType error
         * @param NetConnectionPointer connect
         */
        virtual void doOnConnectionLeave(const NetErrorType&,
            NetConnectionPointer) = 0 ;
        /**
         * @brief check is client message is valid
         *
         * @param db
         * @param nc
         *
         * @return true for ok
         */
        virtual bool doIsValidMessage(const DataType& db,
            NetConnectionPointer nc) const = 0 ;
        /**
         * @brief check if the client is registered
         *
         * @param nc
         *
         * @return trur for ok
         */
        virtual bool doIsRegisterConnection(NetConnectionPointer nc) const = 0 ;
        /**
         * @brief in this function register all the message callbacks.
         */
        virtual void doRegisterActions() = 0 ;
        // no group
        virtual void doDealBackServerPostMessage(const DataType& db,
            PlayerGroup const& group) = 0;
        virtual void doDealBackServerGroupMessage(const MiniGroup&,
            const DataType& db,
            PlayerGroup const& clientsIds) = 0;
        /**
         * @brief if the server has other special action or service. do it here
         * default is nothing if as simple front server
         */
        virtual void doInitOtherService() {} // do nothing default
        virtual void doBindPollManager(ZPollInManager* /*mgr*/) {} // normal we do nothing for bind poll mgr
        /**
         * @brief start the service..
         * default just call init make it as a simple server
         */
        virtual void doStart() { init();}
        second_tt m_maxAnswerTime;

        bool m_hasBack;
        bool isConnectedToBack() const { return m_hasBack;}
        typedef boost::container::deque<DataType> UngentMessageGroup ;
        typedef UngentMessageGroup HardCoreDelayedMessageGroup ;
        HardCoreDelayedMessageGroup m_canDelayedMessage;
        UngentMessageGroup m_ungentMessage;
        typedef UngentMessageGroup NormalMessageGroup ;
        NormalMessageGroup m_waitingPostMessage;
        void sendFastMessage() ;

        void sendWaitingMessage(size_t maxSendSize, UngentMessageGroup& messages);
        size_t m_hard_system_prepared_message_limit ;
        void absorbDelaySystemMessage() ;
        void dispatchBackServerMessage(const DataType&) ;
        void dispatchBackServerBroadcastMessage(const DataType&) ;
        size_t m_ungentMaxSendSize;
        void sendNormalMessage() ;
        size_t m_normal_max_send_size;
        void removePlayerFromPlayerSet(NetConnectionPointer nc);

        typedef Utility::CircleActor<Utility::DelayMessageDealer> DelayMessageActor ;

        DelayMessageActor m_delayActor;
        enum { MaxDelayTime = 10 } ;

        typedef boost::multi_index::multi_index_container<
          std::shared_ptr<FrontClientStub>,
          boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<sortByConnection<FrontClientStub>>,
          boost::multi_index::ordered_non_unique<sortById<FrontClientStub>>,
            boost::multi_index::ordered_non_unique<sortBySession<FrontClientStub>>
            > > ClientSet;

        ClientSet m_justConnected;
        ClientSet m_justLoggining;
        ClientSet m_jsutLogged;
      protected:
        void makeClientLoginning(NetConnectionPointer nc);
        void makeClientLoginned(NetConnectionPointer nc);

    } ;
  }
}
#endif
