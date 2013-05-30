/*
 * =====================================================================================
 *
 *       Filename:  ZSlaveServerSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年03月26日 10时16分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSLAVESERVERSOCKET_H
#define FND_WEBGAME_ZSLAVESERVERSOCKET_H
#include <utility>
#include <memory>
#include <string>
#include <functional>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/lock.hpp>
#include <boost/thread/lock_guard.hpp>
#include <pantheios/assert.h>
#include "ZSocketDef.h"
#include "ZPollInManager.h"
#include "webgame/server/ZSocketUtility.h"

namespace WebGame
{
template<typename SD,
         typename RD,
         typename C = std::vector<SD> >
class ZSlaveServerSocket
{
public:
    typedef SD send_data_type ;
    typedef RD read_data_type ;
    typedef C container_type ;
    typedef ZSlaveServerSocket<SD, RD, C> class_type ;
    typedef std::unique_ptr<ZSlaveServerSocket<SD, RD, C> > pointer ;

    typedef std::function<void (std::shared_ptr<RD>)> MessageDealerFunctionType ;

    ZSlaveServerSocket(class_type const&) = delete ;
    class_type& operator = (ZSlaveServerSocket const&) = delete ;

    ZSlaveServerSocket(
        boost::asio::strand& strand,
        QSocketTratis::context_t& ctx,
        std::string const& name,
        std::string const& subaddress,
        std::string const& socketaddress,
        NeedLingerOption nl = NEED_LINGER,
        std::string const& default_filter = "") :
        //m_subscriber(new socket_t(ctx, XS_SUB)),
        //m_socket(new socket_t(ctx, XS_DEALER)),
        m_strand(strand),
        m_subscriber(new QSocketTratis::socket_t(ctx, QSocketTratis::type_sub())),
        m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::type_dealer())),
        m_name(name),
        m_send_data {},
                m_dealer_function {},
                m_subscriber_function {},
    m_HWM(1000) {
        init(socketaddress, subaddress, nl == NEED_LINGER, default_filter) ;
    }

    ZSlaveServerSocket(
        boost::asio::strand& strand,
        QSocketTratis::context_t& ctx,
                       std::string const& name,
                       std::string const& socketaddress,
                       NeedLingerOption nl = NEED_LINGER) :
      m_strand(strand),
        m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::type_dealer())),
        //m_socket(new socket_t(ctx, XS_DEALER)),
        m_name(name),
        m_HWM(1000) {
        init(socketaddress, std::string(), nl == NEED_LINGER, std::string()) ;
    }

    ~ZSlaveServerSocket() = default ;

    void send_message(send_data_type d) const {
      boost::lock_guard<boost::mutex> lock(m_mutex);
        m_send_data.push_back(d) ;
    }

    bool is_busy() const {
      boost::lock_guard<boost::mutex> lock(m_mutex);
      return !m_send_data.empty() ;
    }

    template<typename M>
    void send_message(M&& msg, player_tt pid = player_tt(0)) const {
        send_message(easy_data_block_cache(std::forward<M>(msg), pid)) ;
    }

    void bind_to_poll_manager(ZPollInManager* mgr, MessageDealerFunctionType const& func_d,
                              MessageDealerFunctionType const& func_s) {
        m_dealer_function = func_d ;
        m_subscriber_function = func_s ;

        mgr->register_absolute_actor(std::bind(&class_type::send, this)) ;
        mgr->register_actor(*m_socket, std::bind(&class_type::recv, this)) ;
        if(m_subscriber)
            mgr->register_actor(*m_subscriber, std::bind(&class_type::recv_subscriber_message, this)) ;
    }

    void bind_to_poll_manager(ZPollInManager* mgr,
                              MessageDealerFunctionType const& func_d) {
        m_dealer_function = func_d ;
        mgr->register_absolute_actor(std::bind(&class_type::send, this)) ;
        mgr->register_actor(*m_socket, std::bind(&class_type::recv, this)) ;
        assert(!m_subscriber) ;

    }

    void bind_to_poll_manager(ZPollInManager* mgr) {
        mgr->register_absolute_actor(std::bind(&class_type::send, this)) ;
    }

private:
    boost::asio::strand& m_strand;
    ZSocketPointer m_subscriber ;
    ZSocketPointer m_socket;
    const std::string m_name ;
    mutable C m_send_data ;
    MessageDealerFunctionType m_dealer_function ;
    MessageDealerFunctionType m_subscriber_function ;
    const int m_HWM ;
    mutable boost::mutex m_mutex;

    void send() {
        C data;
        {
          boost::lock_guard<boost::mutex> lock(m_mutex);
          data.swap(m_send_data);
        }
        if(!data.empty()) 
            QSocketTratis::sendAllGroupMessage(std::move(data), *m_socket) ;

    }

    void recv() {
        QSocketTratis::absorbAndDispatchMessage<read_data_type>(
            *m_socket, m_dealer_function, m_strand) ;
    }

    void recv_subscriber_message() {
        PANTHEIOS_ASSERT(m_subscriber) ;
        QSocketTratis::absorbAndDispatchMessage<read_data_type>(
            *m_subscriber, m_subscriber_function, m_strand) ;
    }

    void init(const std::string& socketaddress,
              const std::string& subaddress,
              bool need_linger,
              const std::string& default_filter) {
        if(need_linger) {
            int linger = 0 ;
            if(m_subscriber) m_subscriber->setsockopt(QSocketTratis::option_linger(), &linger, sizeof linger) ;
            m_socket->setsockopt(QSocketTratis::option_linger(), &linger, sizeof linger) ;
        }

        if(m_subscriber) {
            m_subscriber->setsockopt(QSocketTratis::option_subscribe(),
                default_filter.data(),
                default_filter.size()) ;
            m_subscriber->connect(subaddress.c_str()) ;
        }

        m_socket->setsockopt(QSocketTratis::option_identity(), m_name.c_str(), m_name.size()) ;
        m_socket->connect(socketaddress.c_str()) ;
    }
} ;
}
#endif
