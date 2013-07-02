/*
 * =====================================================================================
 *
 *       Filename:  DefaultZBackServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/21 10:29:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_DEFAULTZBACKSERVER_H
#define FND_WEBGAME_DEFAULTZBACKSERVER_H
#include <memory>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include "webgame/shared/Platform.h"
#include "webgame/message/DataCache.h"
#include "webgame/message/MakeCacheMessage.h"
#include "webgame/netcore/TimerEventFwd.h"
#include "webgame/server/ZMasterServerSocket.h"
#include "webgame/utility/MessageManager.h"
#include "webgame/utility/TimeoutQueue.h"
#ifndef WIN32
#include <folly/FBVector.h>
#endif

namespace WebGame {
namespace Server {
  class ZPollInManager;
  struct ServerOption;
  class DefaultZBackServer : boost::noncopyable {
    public:
      typedef Message::DataBlock::DecoderType DecoderType;
      typedef ServerOption OptionType;
      typedef Message::DataBlock DataType;
      void bindPollManager(ZPollInManager* mgr);
      void start() {
        doStart();
        makeDecorderLocked();
      }

#ifdef WIN32
      typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
      typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
      typedef ZMasterServerSocket<Message::DataCache::const_pointer,
              DataType, SocketDataVector> ZSocketType;

    private:
      void makeDecorderLocked();
    protected:
      typedef std::pair<const std::string&,
              const std::shared_ptr<ZSocketType::ReadDataType>&> FrontMessageType;
      void init();
      typedef QSocketTraits::context_t ContextType;
      typedef boost::asio::strand Strand;
      int secondPerTick() const { return m_tickUsedSeconds;}
      int64_t nowTick() { return m_currentTicks;}
      Utility::TimeoutQueue::Id addTimer(int64_t delay,
                                         Utility::TimeoutQueue::Callback callback) {
        return m_timeoutQueue.add(nowTick(), delay, std::move(callback));
      }

      Utility::TimeoutQueue::Id
        addLoopTimer(int64_t inteval, Utility::TimeoutQueue::Callback callback) {
        return m_timeoutQueue.addRepeating(nowTick(), inteval, std::move(callback));
      }

      Utility::TimeoutQueue::Id
        addLoopTimerWithDelay(int64_t inteval, int64_t delay,
                              Utility::TimeoutQueue::Callback callback) {
        return m_timeoutQueue.addRepeatingWithDelay(nowTick(),
                                           delay,
                                           inteval,
                                           std::move(callback));
      }
    protected:
      typedef Utility::MessageManager<int, FrontMessageType> MessageDealerType;
    private:
      virtual void doStart() { init(); }
      virtual void doInitProperty() {}
      virtual void doTick() {}
      virtual void doInitCallback() = 0;
      // data
    private:
      ContextType* m_zeroContext;
      std::unique_ptr<ZSocketType> m_socket;
      Strand* m_readStrand;
      Strand* m_writeStrand;
      std::unique_ptr<DecoderType> m_decoder;
      NetCore::TimerEventPonter m_clockTimer;
      std::string m_propertyFile;
      int m_tickUsedSeconds;
      int64_t m_currentTicks;
      Utility::TimeoutQueue m_timeoutQueue;
      std::string m_publishAddress; // pushlish message all client
      std::string m_socketAddress; // send message to single client
      MessageDealerType m_frontMessageDealer;

      void initProperty();
      void registerDefaultTimer();
      void initCallback();
      void connectToFront();
      void tick();
      void dealFrontMessage(const std::string& frontName,
                            std::shared_ptr<ZSocketType::ReadDataType> db);

    public:
      ~DefaultZBackServer() NOEXCEPT;
    protected:
      explicit DefaultZBackServer(const OptionType& option);
      Strand* readStrand() { return m_readStrand;}
      Strand* writeStrand() { return m_writeStrand;}
      ContextType* context() { return m_zeroContext;}
      const std::string& propertyFile() const { return m_propertyFile;}
      void pushlishMessage(const ZSocketType::SendDataType& msg) const {
        m_socket->publishMessage(msg);
      }
      void registerConnectionMessageCallback(
          int k,
          MessageDealerType::function_type const& func) {
        m_frontMessageDealer.add(k, func) ;
      }

      template<typename S, typename M>
      void sendMessage(const S& s, M&& m, player_tt pid) const {
        m_socket->sendMessage(s, std::move(m), pid);
      }

      template<typename S, typename M>
      void sendMessage(const S& s, M&& m) const {
        m_socket->sendMessage(s, std::move(m));
      }
      void sendMessage(const SlaveServerNameType& name,
                       const ZSocketType::SendDataType& msg) const {
        m_socket->sendMessage(name, msg);
      }
      void sendMessage(const std::string& name,
                       const ZSocketType::SendDataType& msg) const {
        m_socket->sendMessage(name, msg);
      }
      DecoderType& decoder() { return *m_decoder;}

  };
}
}
#endif
