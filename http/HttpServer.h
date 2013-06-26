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
#include <memory>
#include <map>
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/network/protocol/http/server.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include "webgame/server/ZSlaveServerSocket.h"
#include "webgame/message/DataCache.h"
#ifndef WIN32
#include <folly/FBVector.h>
#endif
#include <vector>

namespace WebGame {
  namespace Server {
    class ZPollInManager;
    struct ServerOption;
  }
}
namespace WebGame { namespace Server { namespace Http {
  class HttpDealer;
  typedef boost::network::http::async_server<HttpDealer> HttpServer;

  class HttpDealer : boost::noncopyable {
    public:

      typedef Message::DataBlock DataType;
      struct HttpMessage {
        typedef std::shared_ptr<HttpMessage> pointer;
        int64_t Id;
        std::string Information;
        HttpServer::connection_ptr Connection;
      };
      explicit HttpDealer(const ServerOption& option);
      ~HttpDealer();
      typedef HttpServer::request request;
      typedef HttpServer::connection_ptr connection_ptr;
      void operator()(const HttpServer::request& req,
                      HttpServer::connection_ptr conn);
      bool isRunning() const { return m_isRunning.load();}
      void Stop() { m_isRunning = false;}
      void pushMessage(const HttpServer::request& req,
                       const HttpServer::connection_ptr& conn);
      void bindPollManager(ZPollInManager* mgr);
      void pushMessageToBack(const DataType& db) const ;
      void pushCacheMessageToBack(Message::DataCache::const_pointer cache) const {
        m_socket->sendMessage(cache) ;
      }

    private:
      void init(ServerOption const& option);
      virtual void doWork(const HttpServer::request& req,
                          const HttpServer::connection_ptr& conn) = 0;
      boost::mutex m_mutex;
      std::atomic<bool> m_isRunning;
      std::atomic<int64_t> m_startId;
      std::map<int64_t, HttpMessage::pointer> m_stockMessage;
#ifdef WIN32
      typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
      typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
      typedef ZSlaveServerSocket<Message::DataCache::const_pointer,
              DataType, SocketDataVector> ZSocketType;

      std::unique_ptr<ZSocketType> m_socket ;

  };

} } }

#endif
