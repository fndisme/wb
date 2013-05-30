/*
 * =====================================================================================
 *
 *       Filename:  ZDataQuery.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-18 15:00:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZDATAQUERY_H
#define FND_WEBGAME_ZDATAQUERY_H
#include <memory>
#include	<string>
#include <tuple>
#include <type_traits>
#include <functional>
#include "DataCache.h"
#include "game_message.h"
#include "ZSocketDef.h"
#include "ZDataQueryTranslatorParameter.h"
namespace WebGame
{

class ZPollInManager ;
class ZDataQuery
{
public:
    ZDataQuery(QSocketTratis::context_t&, const std::string& initfile) ;
    ~ZDataQuery() ;
    typedef Fnd::data_block data_type ;
    typedef DataCache::const_pointer cache_data_type ;

    typedef ZDataQueryTranslatorParameter TranslateHandleParameter ;
    typedef std::function<void (const data_type&)> message_handler_function ;
    typedef std::function<void (const TranslateHandleParameter&)> message_translater_function ;
    void register_handler(int msgtype, const message_handler_function& handler) ;
    void register_tranlater(int msgtype, const message_translater_function& tranlator) ;
    void bind_to_poll_manager(ZPollInManager* mgr) ;
    void lock() ;
    data_type translate_message(int hint, const Fnd::data_block& db) const ;
    void query(const Fnd::data_block& db) ;
    void cache_query(cache_data_type) ;

    template<typename T>
    void message_query(T&& msg, player_tt pid = player_tt(0)) {
        static_assert(std::is_reference<T>::value ||
                      std::is_rvalue_reference<decltype(msg)>::value,
                      "need ref or rvalue") ;

        // static_assert(std::is_reference<T>::value, "msg must be ref") ;
        cache_query(easy_data_block_cache(std::forward<T>(msg), pid)) ;
    }
private:
    class Impl ;
    std::unique_ptr<Impl> m_impl ;
    ZDataQuery(ZDataQuery const&) = delete ;
    ZDataQuery& operator = (const ZDataQuery&) = delete ;

} ;
}
#endif
