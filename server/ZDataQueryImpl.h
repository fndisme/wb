/*
 * =====================================================================================
 *
 *       Filename:  ZDataQueryImpl.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-18 15:08:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZDATAQUERYIMPL_H
#define FND_WEBGAME_ZDATAQUERYIMPL_H
#include <deque>
#include "webgame/server/ZDataQuery.h"
#include "webgame/utility/MessageManager.h"
#include "webgame/message/DataCache.h"
#include <folly/FBVector.h>

namespace WebGame
{
  namespace Server {
    class ZDataQuery::Impl
    {
      public:
        ~Impl() ;
      private:
        friend class ZDataQuery ;
        typedef ZDataQuery::data_type data_type ;
        Impl(QSocketTratis::context_t& ctx,
            boost::asio::strand&,
            const std::string& init_file) ;
        typedef ZDataQuery::message_handler_function message_handler_function ;
        typedef ZDataQuery::message_translater_function message_translater_function ;
        typedef Utility::MessageManager<int, data_type> MessageHandlerGroupType ;
        typedef ZDataQuery::TranslateHandleParameter TranslateHandleParameter ;
        typedef Utility::MessageManager<int, TranslateHandleParameter> MessageTranslaterGroupType ;
        boost::asio::strand& m_strand;
        MessageHandlerGroupType m_handlers ;
        MessageTranslaterGroupType m_translaters ;

        void bindPollManager(ZPollInManager* mgr) ;

        void registerHandler(int msgtype, const message_handler_function& func) {
          m_handlers.add(msgtype, func) ;
        }

        void registerTranslater(int msgtype, const message_translater_function& func) {
          m_translaters.add(msgtype, func);
        }
        data_type translateMessage(int hint, const data_type& d) const ;
        void dealMessage() ;
        void sendQuery() ;
        typedef ZDataQuery::cache_data_type cache_data_type ;
        void query(const data_type& db) {
          m_send_messages.push_back(makeCached(db)) ;
        }
        void query(cache_data_type cache) {
          m_send_messages.push_back(cache) ;
        }
        void lock() {
          m_handlers.lock() ;
          m_translaters.lock() ;
        }
        void init(const std::string&) ;
        typedef folly::fbvector<Message::DataCache::const_pointer> MessageGroupType ;
        MessageGroupType m_send_messages ;
        ZSocketPointer m_socket;
        std::string m_name ;
        Impl(Impl const&) = delete ;
        Impl& operator = (Impl const&) = delete ;
    } ;
  }
}
#endif
