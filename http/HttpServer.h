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
#include <cppcms/application.h>
#ifndef WIN32
#include <folly/FBVector.h>
#endif
#include <vector>

namespace cppdb {
    class session;
}
namespace WebGame { namespace Server { namespace Http {
  class HttpLogic;
  class HttpServer : public cppcms::application {
    public:
      typedef cppcms::application base_class;
      HttpServer(cppcms::service& srv, HttpLogic& logic);
      ~HttpServer();
    private:
      typedef booster::shared_ptr<cppcms::http::context> ContextPointer;
      HttpLogic& m_logic;
      std::unique_ptr<cppdb::session> m_dbSession;
      std::atomic<int64_t> m_startSessionId;
      std::atomic<int64_t> m_receiveSessionId;
      void handlePost();
      void redirect();
      void get(std::string no);
      void post();
      void initDb();
      void recordInformation(const std::string& info);
  };
} } }
#endif
