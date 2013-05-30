/*
 * =====================================================================================
 *
 *       Filename:  ZSocketUtility.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-13 10:14:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSOCKET_UTILITY_H
#define FND_WEBGAME_ZSOCKET_UTILITY_H
#include <algorithm>
#include <xs.hpp>
#include <zmq.hpp>
#include <pantheios/assert.h>

namespace WebGame
{
template<typename Container>
void xs_send_scatter_messages_and_clear_container(Container& container,
        xs::socket_t& socket)
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
void xs_send_scatter_message_with_size(Container& container,
                                       xs::socket_t& socket, size_t maxsize)
{
    if(container.size() <= maxsize) xs_send_scatter_messages_and_clear_container(container, socket) ;
    else {
        auto iter = container.begin() ;
        std::advance(iter, maxsize) ;
        Container newgroup;
        std::move(container.begin(), iter, std::back_inserter(newgroup)) ;
        container.erase(container.begin(), iter) ;
        xs_send_scatter_messages_and_clear_container(newgroup, socket) ;
    }
}



template<typename Container>
void xs_send_group_message_and_clear_container(Container& container,
        xs::socket_t& socket)
{
    PANTHEIOS_ASSERT(!container.empty()) ;
    auto iter = container.cbegin(), iter_end = container.cend() ;
    while(true) {
        auto oldpos = iter++ ;
        int sendmore = (iter == iter_end) ? 0 : XS_SNDMORE ;
        auto db = *oldpos;
        // we dont set XS_DONTWAIT so no EAGAIN
        size_t sendsize = socket.send(static_cast<const void*>(db->data()), db->total_size(), sendmore) ;
        PANTHEIOS_ASSERT(sendsize == db->total_size()) ;
        if(!sendmore) break ;
    }
    container.clear() ;
}

template<typename Container>
void xs_send_group_message_with_size(Container& container, xs::socket_t& socket, size_t maxsize)
{
    if(container.size() <= maxsize) xs_send_group_message_and_clear_container(container, socket) ;
    else {
        auto iter = container.begin() ;
        std::advance(iter, maxsize) ;
        Container newcontainer ;
        std::move(container.begin(), iter, std::back_inserter(newcontainer)) ;
        container.erase(container.begin(), iter) ;
        xs_send_group_message_and_clear_container(newcontainer, socket) ;
    }
}
template<typename D, typename Fun>
void xs_absorb_header_and_handle_message(xs::socket_t& socket, const Fun& fun)
{
    xs::message_t headermsg ;
    socket.recv(&headermsg) ;
    std::string header(static_cast<const char*>(headermsg.data()),
                       static_cast<const char*>(headermsg.data()) + headermsg.size()) ;
    int hasmore(0) ;
    size_t more_size = sizeof hasmore ;
    headermsg.getmsgopt(XS_MORE, &hasmore, &more_size) ;

    while(hasmore) {
        xs::message_t msg ;
        socket.recv(&msg);

        D db;
        bool ok = db.import_from_array(static_cast<const void*>(msg.data()), msg.size()) ;
        PANTHEIOS_ASSERT(ok) ;

        fun(std::cref(header), std::cref(db)) ;

        msg.getmsgopt(XS_MORE, &hasmore, &more_size) ;

    }
}


template<typename D, typename Fun>
void xs_absorb_and_handle_message(xs::socket_t& socket, const Fun& fun)
{
    while(true) {
        xs::message_t msg ;
        socket.recv(&msg);

        D db;
        bool ok = db.import_from_array(static_cast<const void*>(msg.data()), msg.size()) ;
        PANTHEIOS_ASSERT(ok) ;

        fun(std::cref(db)) ;

        int has_more(0);
        size_t more_size = sizeof has_more ;
        msg.getmsgopt(XS_MORE, &has_more, &more_size) ;
        if(!has_more) break ;
    }

}
template<typename Container, typename Header>
void xs_send_header_group_message_with_size(Container& container,
        Header&& header,
        xs::socket_t& socket,
        size_t maxsize)
{

    // we not set XS_DONTWAIT do no EAGAIN, if error throw exception
    size_t sendsize = socket.send(static_cast<const void*>(header.data()), header.size(), XS_SNDMORE) ;
    PANTHEIOS_ASSERT(sendsize == header.size()) ;
    xs_send_group_message_with_size(container, socket, maxsize) ;
}
}
#endif
