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
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <cppcms/application.h>
#include "webgame/server/ZSlaveServerSocket.h"
#include "webgame/server/ServerOption.h"
#include "webgame/message/DataCache.h"

namespace WebGame {
  namespace Server {
    class ZPollInManager;
    struct ServerOption;
  }
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
  };
} } }
#endif
