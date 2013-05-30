#ifndef FND_GAME_NET_CONNECTION_STORAGE_H
#define FND_GAME_NET_CONNECTION_STORAGE_H
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif 
#include <boost/aligned_storage.hpp>
#include <boost/asio.hpp>
#include "net_config.h"

namespace WebGame {
    class handle_allocator {
    public:
        handle_allocator() :
          m_storage(),
          m_in_use(false){}
        void* allocate(std::size_t size) {
            if(!m_in_use && size < m_storage.size) {

                m_in_use = true ;
                return m_storage.address() ;
            } else {
                return ::operator new(size) ;
            }
        }

        void deallocate(void* pointer) {
            if(pointer == m_storage.address()) {
                m_in_use = false  ;
            } else {
                ::operator delete(pointer) ;
            }
        }
    private:
        boost::aligned_storage<1024> m_storage ;
        bool m_in_use ;
        handle_allocator(handle_allocator const&) = delete ;
        handle_allocator& operator = (handle_allocator const&) = delete ;

    } ;

    template<typename Handler>
    class custom_alloc_handler {
    public:
        custom_alloc_handler(handle_allocator& a, Handler h) :
            m_allocator(a),
            m_handler(h) {}

        void operator()() {
            m_handler() ;
        }
        template<typename Arg1>
        void operator()(Arg1 arg1) {
            m_handler(arg1) ;
        }

        template<typename Arg1, typename Arg2>
        void operator()(Arg1 a1, Arg2 a2) {
            m_handler(a1,a2) ;
        }

        friend void* asio_handler_allocate(std::size_t size,
                                           custom_alloc_handler<Handler>* this_handler) {
            return this_handler->m_allocator.allocate(size) ;
        }

        friend void asio_handler_deallocate(void* pointer, std::size_t /* size */,
                                            custom_alloc_handler<Handler>* this_handler) {
            this_handler->m_allocator.deallocate(pointer) ;
        }
    private:
        handle_allocator& m_allocator ;
        Handler m_handler ;
    } ;

    template <typename Handler>
    inline
    custom_alloc_handler<Handler> make_custom_alloc_handler(
        handle_allocator& a, Handler h) {
        return custom_alloc_handler<Handler>(a,h) ;
    }
}
#endif
