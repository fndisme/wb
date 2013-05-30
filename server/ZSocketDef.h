/*
 * =====================================================================================
 *
 *       Filename:  ZSocketDef.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-2 16:58:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSOCKETDEF_H
#define FND_WEBGAME_ZSOCKETDEF_H
//#define FND_USE_ZMQ
#include <cstdint>
#include <memory>
#include <boost/asio.hpp>
#ifdef FND_USE_ZMQ
#include "webgame/server/ZMQSocketTraits.h"
#else
#include "webgame/server/XSSocketTraits.h"
#endif
//#include "game_message.h"
#include "webgame/message/DataCache.h"


namespace WebGame {
  namespace Server {
#ifdef FND_USE_ZMQ
  namespace QSocketTratis = ZMQSocketTraits ;
#else
  namespace QSocketTratis = XSSocketTraits;
#endif
  typedef std::unique_ptr<QSocketTratis::socket_t> ZSocketPointer ;
  typedef Message::DataCache::const_pointer ZDataType ;

  enum NeedLingerOption {
    NEED_LINGER,
    DONT_NEED_LINGER
  } ;

  struct ZSockOption {
    NeedLingerOption LingerOption ;
    int HWM ; // high water mark
    uint64_t SwapSize ; // byte

    explicit ZSockOption(
        uint64_t size = 100 * 1024 * 1024, // 100 M disc space
        int hwm = 2000,
        NeedLingerOption lingerOption= NEED_LINGER) :
      LingerOption(lingerOption),
      HWM(hwm),
      SwapSize(size) {}
  } ;
  }
}
#endif
