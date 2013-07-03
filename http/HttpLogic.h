/*
 * =====================================================================================
 *
 *       Filename:  HttpLogic.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/3 10:31:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVER_HPPT_LOGIC_H
#define FND_WEBGAME_SERVER_HPPT_LOGIC_H
#include <atomic>
#include <map>
#include <memory>
#include <string>
#include <boost/bimap.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include "webgame/server/DefaultSlaveSocket.h"

namespace WebGame {
  namespace Server {
    class ZPollInManager;
    namespace Stock {
        class HttpMessage;
    }
  }
}

namespace WebGame { namespace Server { namespace Http {
  class HttpLogic : boost::noncopyable {
    public:
      HttpLogic(cppcms::service& srv, const std::string& initFile);
      void run();
      virtual ~HttpLogic();
      void stop();
      typedef booster::shared_ptr<cppcms::http::context> ContextPointer;
      void addSession(ContextPointer context, int type, const std::string& sendInfo);
      bool isWaitingContext(ContextPointer context) const;
    protected:
      cppcms::service& service() { return m_service;}
      void sendMessage(ContextPointer context, const std::string& msg);
    private:
      typedef Message::DataBlock DataType;
      typedef Message::DataBlock::DecoderType DecoderType;

      typedef SlaveSocket ZSocketType;
      cppcms::service& m_service;
      std::string m_initFile;
      std::atomic<bool> m_isRunning;
      std::atomic<int64_t> m_startSessionId;
      mutable boost::mutex m_mutex;
      std::unique_ptr<QSocketTraits::context_t> m_context;
      std::unique_ptr<ZSocketType> m_socket;
      std::unique_ptr<DecoderType> m_decoder;
      typedef boost::bimap<int64_t, ContextPointer> BimapType;
      BimapType m_sessions;
      int m_inteval;
      void uninit();
      void init();
      void initDecoder();
      bool initContext();
      void registerActions();
      virtual void doRegisterActions() {}
      void bindPollManager(ZPollInManager* mgr);
      void handleMessage(std::shared_ptr<DataType> d);
      ContextPointer releaseContext(int64_t);
      virtual void doDispatch(ContextPointer,
                              const std::shared_ptr<const Server::Stock::HttpMessage>&) {
      }
      virtual void doDispatchServerMessage(
          const std::shared_ptr<const Server::Stock::HttpMessage>&) {
      }
      void removeContext(ContextPointer);
  };

} } }

#endif
