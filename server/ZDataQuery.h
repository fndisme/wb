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
#include "webgame/message/DataCache.h"
#include "webgame/message/DataBlock.h"
#include "webgame/server/ZSocketDef.h"
#include "webgame/server/ZDataQueryTranslatorParameter.h"
namespace WebGame {
namespace Server {

class ZPollInManager ;
class ZDataQuery {
public:
    ZDataQuery(QSocketTratis::context_t&,
        boost::asio::strand&,
        const std::string& initfile) ;
    ~ZDataQuery() ;
    typedef Message::DataBlock data_type ;
    typedef Message::DataCache::const_pointer cache_data_type ;

    typedef ZDataQueryTranslatorParameter TranslateHandleParameter ;
    typedef std::function<void (const data_type&)> message_handler_function ;
    typedef std::function<void (const TranslateHandleParameter&)> message_translater_function ;
    void registerHandler(int msgtype, const message_handler_function& handler) ;
    void registerTranslater(int msgtype, const message_translater_function& tranlator) ;
    void bindPollManager(ZPollInManager* mgr) ;
    void lock() ;
    data_type translateMessage(int hint, const data_type& db) const ;
    void query(const data_type& db) ;
    void cacheQuery(cache_data_type) ;

    template<typename T>
    void messageQuery(T&& msg, player_tt pid = player_tt(0)) {
        static_assert(std::is_reference<T>::value ||
                      std::is_rvalue_reference<decltype(msg)>::value,
                      "need ref or rvalue") ;

        // static_assert(std::is_reference<T>::value, "msg must be ref") ;
        cacheQuery(easy_data_block_cache(std::forward<T>(msg), pid)) ;
    }
private:
    class Impl ;
    std::unique_ptr<Impl> m_impl ;
    ZDataQuery(ZDataQuery const&) = delete ;
    ZDataQuery& operator = (const ZDataQuery&) = delete ;

} ;
}
}
#endif
