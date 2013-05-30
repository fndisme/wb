/*
 * =====================================================================================
 *
 *       Filename:  ZMasterServerSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年03月26日 13时08分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZMASTERSERVERSOCKET_H
#define FND_WEBGAME_ZMASTERSERVERSOCKET_H
#include <string>
#include <utility>
#include <algorithm>
#include <memory>
#include <boost/asio.hpp>
#include <boost/container/flat_map.hpp>
#include "ZSocketDef.h"
#include "ZSlaveDef.h"
#include "ZPollInManager.h"
#include "ZSocketUtility.h"
#include "identity_type.h"
#include <pantheios/assert.h>

namespace WebGame
{
template<typename SD,
         typename RD,
         typename C = std::vector<SD> >
class ZMasterServerSocket
{
public:
    typedef SD send_data_type ;
    typedef send_data_type CacheDataType ;
    typedef RD read_data_type ;
    typedef C container_type ;
    typedef ZMasterServerSocket<SD, RD, C> class_type ;
    typedef std::unique_ptr<ZMasterServerSocket<SD, RD, C> > pointer ;

    typedef std::function<void (const std::string& , std::shared_ptr<RD>)>
      MessageDealerFunctionType ;
    typedef boost::container::flat_map<SlaveServerNameType, container_type> MessageGroupType ;

    enum DirectionEnum {
        ZM_BOTH,
        ZM_RECEIVE
    } ;

    class_type& operator = (class_type const&) = delete ;
    ZMasterServerSocket(class_type const&) = delete ;

    ZMasterServerSocket(
        boost::asio::strand& strand,
        QSocketTratis::context_t& ctx,
        std::string const& publishaddress,
        std::string const& socketaddress,
        const ZSockOption& option = ZSockOption()) :
      m_strand(strand),
      m_publisher(new QSocketTratis::socket_t(ctx, QSocketTratis::typePub())),
      m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::typeRouter())),
      m_messages {},
      m_publish_message {},
      m_HWM(option.HWM != 0 ? option.HWM : 1000) {

        init(publishaddress, socketaddress, option.LingerOption == NEED_LINGER) ;
      }

    ZMasterServerSocket(
        boost::asio::strand& strand,
        QSocketTratis::context_t& ctx,
        std::string const& socketaddress,
        const ZSockOption& option = ZSockOption()) :
        m_strand(strand),
        m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::type_router())),
        m_HWM(option.HWM != 0 ? option.HWM : 1000) {
        init(std::string(), socketaddress, option.LingerOption == NEED_LINGER) ;

    }

    void send_message(const SlaveServerNameType& name, send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_messages[name].push_back(msg) ;
    }

    void send_message(const std::string& name, send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_messages[SlaveServerNameType(name)].push_back(msg) ;
    }


    void publish_message(send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        PANTHEIOS_ASSERT(m_publisher) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_publish_message.push_back(msg) ;
    }

    template<typename M>
    void send_message(const SlaveServerNameType& name, M&& msg, player_tt pid = player_tt(0)) const {
        send_message(name, easy_data_block_cache(msg, pid)) ;
    }

    template<typename M>
    void send_message(const std::string& name, M&& msg, player_tt pid = player_tt(0)) const {
        send_message(name, easy_data_block_cache(msg, pid)) ;
    }

    template<typename M>
    void publish_message(M&& msg) const {
        publish_message(easy_data_block_cache(msg, player_tt(0))) ;
    }

    void bind_to_poll_manager(ZPollInManager* mgr,
                              const MessageDealerFunctionType& func,
                              DirectionEnum direction = ZM_BOTH) {
        if(direction == ZM_BOTH) {
            mgr->register_absolute_actor(std::bind(&class_type::send_to_slave, this)) ;
            if(m_publisher) mgr->register_absolute_actor(std::bind(&class_type::send_publish_message, this)) ;
        }

        m_dealer_function = func ;
        mgr->register_actor(*m_socket, std::bind(&class_type::recv, this)) ;
    }

private:
    boost::asio::strand& m_strand;
    ZSocketPointer m_publisher ;
    ZSocketPointer m_socket ;

    mutable MessageGroupType m_messages ;
    mutable container_type m_publish_message ;

    MessageDealerFunctionType m_dealer_function ;
    const int m_HWM ; /// high water mark
    mutable boost::mutex m_mutex;

    void recv() {
        QSocketTratis::absorbHeaderDispatchMesage<read_data_type>(*m_socket, m_dealer_function, m_strand) ;
    }

    void send_publish_message() {
        PANTHEIOS_ASSERT(m_publisher) ;

      container_type data;
      {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        data.swap(m_publish_message);
      }
        QSocketTratis::sendScatterMessage(data,
                *m_publisher, m_HWM) ;
    }

    void send_to_slave() {

      MessageGroupType messages;
      {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        messages.swap(m_messages);
      }
    
      for(auto& v : messages) {
        if(v.second.empty()) continue;
        QSocketTratis::sendAllGroupMessage(v.second, v.first.get(),
                    *m_socket) ;
      }
    }

    void init(const std::string& publishaddress,
              const std::string& socketaddress,
              bool need_linger) {
        if(m_publisher)
            m_publisher->setsockopt(QSocketTratis::option_send_high_water_mark(),
                                    &(m_HWM), sizeof(m_HWM)) ;
        m_socket->setsockopt(QSocketTratis::option_send_high_water_mark(),
                             &(m_HWM), sizeof(m_HWM)) ;


        if(m_publisher)
            m_publisher->bind(publishaddress.c_str()) ;

        m_socket->bind(socketaddress.c_str()) ;

        if(need_linger) {
            int linger = 0 ;
            if(m_publisher)
                m_publisher->setsockopt(QSocketTratis::option_linger(),
                                        &linger, sizeof linger) ;
            m_socket->setsockopt(QSocketTratis::option_linger(),
                                 &linger, sizeof linger) ;

        }
    }
} ;
}


#endif
