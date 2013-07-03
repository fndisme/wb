/*
 * =====================================================================================
 *
 *       Filename:  DefaultSlaveSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/7/3 11:06:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVER_DEFAULT_SLAVESOCKET_H
#define FND_WEBGAME_SERVER_DEFAULT_SLAVESOCKET_H
#ifndef WIN32
#include <folly/FBVector.h>
#else
#include <vector>
#endif
#include "webgame/message/DataBlock.h"
#include "webgame/message/DataCache.h"
#include "webgame/server/ZSlaveServerSocket.h"

namespace WebGame { namespace Server {
#ifdef WIN32
      typedef std::vector<Message::DataCache::const_pointer> SocketDataVector;
#else
      typedef folly::fbvector<Message::DataCache::const_pointer> SocketDataVector ;
#endif
      typedef ZSlaveServerSocket<Message::DataCache::const_pointer,
              Message::DataBlock, SocketDataVector> SlaveSocket;

}}


#endif
