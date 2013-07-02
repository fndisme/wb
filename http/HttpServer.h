/*
 * =====================================================================================
 *
 *       Filename:  HttpServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/26 14:14:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAEM_SERVER_HTTP_HTTPSERVER_H
#define FND_WEBGAEM_SERVER_HTTP_HTTPSERVER_H
#include <atomic>
#include <list>
#include <memory>
#include <map>
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <cppcms/application.h>
#include "webgame/server/ZSlaveServerSocket.h"
#include "webgame/server/ServerOption.h"
#include "webgame/message/DataCache.h"
#ifndef WIN32
#include <folly/FBVector.h>
#endif
#include <vector>

namespace WebGame {
  namespace Server {
    class ZPollInManager;
    namespace Stock {
        class HttpMessage;
    }
  }
}
namespace cppdb {
    class session;
}
namespace WebGame { namespace Server { namespace Http {
  class HttpServer : public cppcms::application {
    public:
      typedef cppcms::application base_class;
      HttpServer(cppcms::service& srv, const std::string& initFile);
      ~HttpServer();
      virtual void main(std::string url);
      void transferMessageWithOther();
      void stop() { m_isRunning.store(false);}
    private:
      std::unique_ptr<QSocketTraits::context_t> m_context;
      std::atomic<bool> m_isRunning;
      std::string m_initFile;
      void bindPollManager(ZPollInManager* mgr);
      void initResource();
      void releaseResource();

      typedef Message::DataBlock DataType;
      typedef Message::DataBlock::DecoderType DecoderType;
#ifdef WIN32
      typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
      typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
      typedef ZSlaveServerSocket<Message::DataCache::const_pointer,
              DataType, SocketDataVector> ZSocketType;
      void removeContext(booster::shared_ptr<cppcms::http::context> context);
      typedef booster::shared_ptr<cppcms::http::context> ContextPointer;
      typedef std::shared_ptr<WebGame::Server::Stock::HttpMessage> MessagePointer;
      typedef std::pair<ContextPointer, MessagePointer> StockMessage;
      std::map<int64_t, StockMessage> m_stockMessages;
      std::map<ContextPointer, std::list<int64_t>> m_contextPointers;
      std::unique_ptr<ZSocketType> m_socket;
      std::unique_ptr<DecoderType> m_decoder;
      std::unique_ptr<cppdb::session> m_dbSession;
      void registerActions();
      int64_t m_startSesionId;
      void handlePost();
      void redirect();
      void get(std::string no);
      void post();
      void initDb();
      void recordInformation(const std::string& info);
  };
} } }
#endif
