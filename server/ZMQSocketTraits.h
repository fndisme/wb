/*
 * =====================================================================================
 *
 *       Filename:  ZMQSocketTraits.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年01月04日 10时49分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZMQSOCKETTRAITS_H
#define FND_WEBGAME_ZMQSOCKETTRAITS_H
#include <zmq.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>
namespace WebGame
{
namespace ZMQSocketTraits
{
typedef zmq::socket_t socket_t ;
typedef zmq::context_t context_t ;
typedef zmq::message_t message_t ;
typedef zmq::pollitem_t pollitem_t ;
constexpr int event_pollin()
{
    return ZMQ_POLLIN ;
}
constexpr int option_identity()
{
    return ZMQ_IDENTITY ;
}
constexpr int option_linger()
{
    return ZMQ_LINGER ;
}
constexpr int type_dealer()
{
    return ZMQ_DEALER ;
}
constexpr int type_sub()
{
    return ZMQ_SUB ;
}
constexpr int option_subscribe()
{
    return ZMQ_SUBSCRIBE ;
}
constexpr int type_pub()
{
    return ZMQ_PUB ;
}
constexpr int type_router()
{
    return ZMQ_ROUTER ;
}
constexpr int option_send_high_water_mark()
{
    return ZMQ_SNDHWM ;
}
template<typename C>
int poll(C& c, long timeout)
{
    return zmq::poll(&(c[0]), c.size(), timeout) ;
}

inline int wait(long timeout)
{
    return zmq::poll(nullptr, 0, timeout) ;
}

template<typename Container>
void send_scatter_messages_and_clear_container(Container& container,
        socket_t& socket)
{
    if(container.empty()) return ;
    std::for_each(container.cbegin(), container.cend(),
    [&socket](typename Container::const_reference v) {
        size_t sendsize = socket.send(v->data(), v->total_size()) ; // we dont
        // set XS_DONTWAIT, SO no EAGAIN
        PANTHEIOS_ASSERT(sendsize == v->total_size()) ;
    }) ;
    container.clear() ;
}

template<typename Container>
void send_scatter_message_with_size(Container& container,
                                    socket_t& socket, size_t maxsize)
{
    if(container.size() <= maxsize) send_scatter_messages_and_clear_container(container, socket) ;
    else {
        auto iter = container.begin() ;
        std::advance(iter, maxsize) ;
        Container newgroup(std::make_move_iterator(container.begin()), 
            std::make_move_iterator(iter)) ;
        //std::move(container.begin(), iter, std::back_inserter(newgroup)) ;
        container.erase(container.begin(), iter) ;
        send_scatter_messages_and_clear_container(newgroup, socket) ;
    }
}


template<typename Container>
void send_group_message_and_clear_container(Container& container,
        socket_t& socket)
{
    PANTHEIOS_ASSERT(!container.empty()) ;
    auto iter = container.cbegin(), iter_end = container.cend() ;
    while(true) {
        auto oldpos = iter++ ;
        int sendmore = (iter == iter_end) ? 0 : ZMQ_SNDMORE ;
        auto db = *oldpos;
        // we dont set ZMQ_DONTWAIT so no EAGAIN
        size_t sendsize = socket.send(static_cast<const void*>(db->data()), db->total_size(), sendmore) ;
        PANTHEIOS_ASSERT(sendsize == db->total_size()) ;
        if(!sendmore) break ;
    }
    PANTHEIOS_ASSERT(iter == iter_end) ;
    container.clear() ;
}

template<typename Container>
void send_group_message_with_size(Container& container, socket_t& socket, size_t maxsize)
{
    if(container.size() <= maxsize) send_group_message_and_clear_container(container, socket) ;
    else {
        auto iter = container.begin() ;
        std::advance(iter, maxsize) ;
        Container newcontainer(std::make_move_iterator(container.begin()),
            std::make_move_iterator(iter)) ;
        //std::move(container.begin(), iter, std::back_inserter(newcontainer)) ;
        container.erase(container.begin(), iter) ;
        send_group_message_and_clear_container(newcontainer, socket) ;
    }
}


template<typename D, typename Fun>
void absorb_header_and_handle_message(socket_t& socket, const Fun& fun)
{
    message_t headermsg ;
    bool status = socket.recv(&headermsg) ;
    if(!status)  {
        pantheios::log_WARNING("no receive header error ") ;
        return ;
    }
    std::string header(static_cast<const char*>(headermsg.data()),
                       static_cast<const char*>(headermsg.data()) + headermsg.size()) ;
    int hasmore(0) ;
    size_t more_size = sizeof hasmore ;
    socket.getsockopt(ZMQ_RCVMORE, &hasmore, &more_size) ;

    while(hasmore) {
        message_t msg ;
        status = socket.recv(&msg);
        PANTHEIOS_ASSERT(status) ;

        D db;
        bool ok = db.import_from_array(static_cast<const void*>(msg.data()), msg.size()) ;
        if(ok)
            fun(std::cref(header), std::cref(db)) ;
        else {
            pantheios::log_WARNING("not parse db ok..... IGNORE") ;
        }

        socket.getsockopt(ZMQ_RCVMORE, &hasmore, &more_size) ;

    }
}

template<typename D, typename Fun>
void absorb_and_handle_message(socket_t& socket, const Fun& fun)
{
    while(true) {
        message_t msg ;
        bool status = socket.recv(&msg);

        if(!status) break ; // because bolock

        D db;
        bool ok = db.import_from_array(static_cast<const void*>(msg.data()), msg.size()) ;

        if(ok) {
          fun(std::cref(db)) ;
        } else {
          pantheios::log_WARNING("absorb not valid message.... Ignore") ;
        }

        int has_more(0);
        size_t more_size = sizeof has_more ;
        socket.getsockopt(ZMQ_RCVMORE, &has_more, &more_size) ;
        if(!has_more) break ;
    }
}

template<typename Container, typename Header>
void send_header_group_message_with_size(Container& container,
        Header&& header,
        socket_t& socket,
        size_t maxsize)
{

    // we not set ZMQ_DONTWAIT do no EAGAIN, if error throw exception
    size_t sendsize = socket.send(static_cast<const void*>(header.data()), header.size(), ZMQ_SNDMORE) ;
    PANTHEIOS_ASSERT(sendsize == header.size()) ;
    send_group_message_with_size(container, socket, maxsize) ;
}

template<typename Container, typename Header>
void send_header_group_message_and_clean_group(Container& container,
        Header&& header,
        socket_t& socket)
{

    // we not set ZMQ_DONTWAIT do no EAGAIN, if error throw exception
    size_t sendsize = socket.send(static_cast<const void*>(header.data()), header.size(), ZMQ_SNDMORE) ;
    PANTHEIOS_ASSERT(sendsize == header.size()) ;
    send_group_message_and_clear_container(container, socket) ;
}
}
}
#endif

