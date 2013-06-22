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
#ifndef WIN32
#include <folly/FBVector.h>
#endif

namespace WebGame {
namespace Server {
  class ZPollInManager;
  class ServerOption;
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
      void init();
      typedef QSocketTraits::context_t ContextType;
      typedef boost::asio::strand Strand;

    private:
      virtual void doStart() { init(); }
      // data
    private:
      ContextType* m_zeroContext;
      Strand* m_readStrand;
      Strand* m_writeStrand;
      std::unique_ptr<DecoderType> m_decoder;
      NetCore::TimerEventPonter m_clockTimer;
      std::string m_propertyFile;
    public:
      ~DefaultZBackServer() NOEXCEPT;
    protected:
      explicit DefaultZBackServer(const OptionType& option);
      Strand* readStrand() { return m_readStrand;}
      Strand* writeStrand() { return m_writeStrand;}
      ContextType* context() { return m_zeroContext;}
      const std::string& propertyFile() const { return m_propertyFile;}
  };
}
}
#endif
