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
#include "ZDataQuery.h"
#include "message_manager.h"
#include "DataCache.h"
#include <folly/FBVector.h>

namespace WebGame
{
class ZDataQuery::Impl
{
public:
    ~Impl() ;
private:
    friend class ZDataQuery ;
    typedef ZDataQuery::data_type data_type ;
    Impl(QSocketTratis::context_t& ctx, const std::string& init_file) ;
    typedef ZDataQuery::message_handler_function message_handler_function ;
    typedef ZDataQuery::message_translater_function message_translater_function ;
    typedef Utility::message_manager<int, data_type> MessageHandlerGroupType ;
    typedef ZDataQuery::TranslateHandleParameter TranslateHandleParameter ;
    typedef Utility::message_manager<int, TranslateHandleParameter> MessageTranslaterGroupType ;
    MessageHandlerGroupType m_handlers ;
    MessageTranslaterGroupType m_translaters ;

    void bind_to_poll_manager(ZPollInManager* mgr) ;

    void register_handler(int msgtype, const message_handler_function& func) {
        m_handlers.add(msgtype, func) ;
    }

    void register_tranlater(int msgtype, const message_translater_function& func) {
        m_translaters.add(msgtype, func);
    }
    data_type translate_message(int hint, const data_type& d) const ;
    void deal_message() ;
    void send_query() ;
    typedef ZDataQuery::cache_data_type cache_data_type ;
    void query(const Fnd::data_block& db) {
        m_send_messages.push_back(make_cached(db)) ;
    }
    void query(cache_data_type cache) {
        m_send_messages.push_back(cache) ;
    }
    void lock() {
        m_handlers.lock() ;
        m_translaters.lock() ;
    }
    void init(const std::string&) ;
    typedef folly::fbvector<DataCache::const_pointer> MessageGroupType ;
    MessageGroupType m_send_messages ;
    ZSocketPointer m_socket;
    std::string m_name ;
    Impl(Impl const&) = delete ;
    Impl& operator = (Impl const&) = delete ;
} ;
}
#endif
