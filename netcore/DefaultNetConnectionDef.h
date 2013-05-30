/*
 * =====================================================================================
 *
 *       Filename:  DefaultNetConnectionDef.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012-1-30 13:25:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_DEFAULTNETCONNETIONDEF_H
#define FND_WEBGAME_DEFAULTNETCONNETIONDEF_H
#include <tuple>
#include	<memory>
namespace WebGame {
  namespace Message {
    class DataBlock;
  }
  namespace NetCore {
    struct DefaultConnectionTraits {
      // test using is_void, so default
      typedef Message::DataBlock DataType ;
      typedef void NotLockType ; // not lock
      typedef void ActiveManageMessageType ; // is active
      typedef void NotDelayMessageType ; // no delay
      typedef void ActiveSendHugeData ; // send huge
    } ;
    template<typename ConnectionTraits>
      class Connection;
    typedef Connection<DefaultConnectionTraits> DefaultNetConnectType ;
    typedef std::shared_ptr<DefaultNetConnectType> DefaultNetConnectPointer ;
    typedef std::weak_ptr<DefaultNetConnectType> DefaultNetConnectWeakPointer ;
    typedef std::shared_ptr<const DefaultNetConnectType> DefaultNetConnectConstPointer;
    typedef std::tuple<const Message::DataBlock&, 
            DefaultNetConnectPointer> InnerMessageHandlerType ;
    typedef const InnerMessageHandlerType& MessageHandlerType ;
  }
}
#endif
