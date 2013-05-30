/*
 * =====================================================================================
 *
 *       Filename:  ZSocket_PushPullPair.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-13 13:14:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSOCKET_PUSHPULLPAIR_H
#define FND_WEBGAME_ZSOCKET_PUSHPULLPAIR_H
#include <utility>
#include	<memory>
#include <string>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "ZSocketDef.h"
#include "ZSocketUtility.h"
#include "ZPollInManager.h"

namespace WebGame
{
enum BindConnectOption {
    BIND_ADDRESS,
    CONNECT_ADDRESS
} ;
template<typename SD,
         typename RD,
         typename C = std::vector<SD> >
class ZSocket_PushPullPair : boost::noncopyable
{
public:
    typedef SD send_data_type ;
    typedef RD read_data_type ;
    typedef C container_type ;
    typedef ZSocket_PushPullPair<SD, RD, C> class_type ;
    typedef std::unique_ptr<ZSocket_PushPullPair<SD, RD, C> > pointer ;

    typedef boost::function<void (const RD&)> MessageDealerFunctionType ;


    ZSocket_PushPullPair(xs::context_t& ctx,
                         std::string& puller_address,
                         BindConnectOption pulleroption,
                         std::string& pusher_address,
                         BindConnectOption pusheroption,
                         NeedLingerOption nl = NEED_LINGER) :
        m_pusher(new xs::socket_t(ctx, XS_PUSH)),
        m_puller(new xs::socket_t(ctx, XS_PULL)) {
        if(pulleroption == BIND_ADDRESS) {
            m_puller->bind(puller_address.c_str()) ;
        } else {
            m_puller->connect(puller_address.c_str()) ;
        }

        if(pusheroption == BIND_ADDRESS) {
            m_pusher->bind(pusher_address.c_str()) ;
        } else {
            m_pusher->connect(pusher_address.c_str()) ;
        }

        if(nl == NEED_LINGER) {
            int linger = 0 ;
            m_puller->setsockopt(XS_LINGER, &linger, sizeof linger) ;
            m_pusher->setsockopt(XS_LINGER, &linger, sizeof linger) ;
        }
    }

    void bind_to_poll_manager(ZPollInManager* mgr, C* send_data,
                              MessageDealerFunctionType const& fun) {
        m_datas = send_data ;
        m_dealer_function = fun ;

        mgr->register_absolute_actor(boost::bind(&class_type::send,
                                     this)) ;
        mgr->register_actor(*m_puller, boost::bind(&class_type::recv,
                            this)) ;

    }

    void send() {
        if(!m_datas->empty())
            send_group_message_and_clear_container(*m_datas, *m_pusher) ;
    }

    void recv() {
        absorb_and_handle_message<read_data_type>(*m_puller, m_dealer_function) ;
    }

private:
    ZSocketPointer m_pusher ;
    ZSocketPointer m_puller ;
    C* m_datas ;
    MessageDealerFunctionType m_dealer_function ;
} ;
}

#endif
