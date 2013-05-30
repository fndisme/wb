/*
 * =====================================================================================
 *
 *       Filename:  PoolBuffer.h
 *
 *    Description:  
 * =====================================================================================
 */
#ifndef FND_WEB_GAME_POOL_BUFFER_H
#define FND_WEB_GAME_POOL_BUFFER_H
#include <stlsoft/memory/auto_buffer.hpp>
namespace WebGame {
  namespace NetCore {
    // FIXME
    // IT's NOT a safe class. just use in some class. should not use as single
    // part
  template<int N>
    class PoolBuffer {
      public:
        typedef PoolBuffer<N> class_type ;
        inline char* data() { return m_buffer.data();}
        inline void* appendDataAddress() { return (void*)(m_buffer.data() + m_used) ;}
        inline const char* data() const {return m_buffer.data();}
        inline size_t capacity() const { return m_buffer.size();}
        inline int avaliableBytes() const { return capacity() - m_used;}
        explicit PoolBuffer(size_t bsize) ;
        inline size_t size() const { return m_used;}
        inline void size(size_t s) { m_used = s ;}
        void resetCapacity(size_t new_capacity) ;
        inline void clear() { size(0); }
        // is not safe, but because we show Data to user. it can not be safe
        inline void append(size_t s) { m_used += s ;}
        PoolBuffer(class_type&& rhs) : m_buffer(1),
        m_used(rhs.m_used) {
          rhs.m_buffer.swap(m_buffer) ;
          rhs.m_used = 0 ;
        }
      private:
        typedef stlsoft::auto_buffer<char, N> buffer_t ;
        PoolBuffer(class_type const&) = delete ;
        PoolBuffer& operator = (class_type const&) = delete ;
        buffer_t m_buffer ;
        size_t m_used ;
    } ;

  template<int N>
    PoolBuffer<N>::PoolBuffer(size_t bsize) :
      m_buffer(bsize),
      m_used(0) {
      }
  template<int N>
    void PoolBuffer<N>::resetCapacity(size_t new_capacity) {
      clear() ;
      if(new_capacity <= capacity()) return ;
      m_buffer.resize(1) ;
      m_buffer.resize(new_capacity) ;
    }
}
}
#endif
