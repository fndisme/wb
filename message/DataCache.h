/*
 * =====================================================================================
 *
 *       Filename:  DataCache.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-10-31 14:50:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_DATACACHE_H
#define FND_WEBGAME_DATACACHE_H
#include <cstring>
#include	<stdexcept>
#include	<memory>
#include	<type_traits>
#include <functional>
#include <stlsoft/memory/auto_buffer.hpp>
#include <pantheios/assert.h>
#include "webgame/message/DataBlock.h"
//#include "game_message_util.h"

namespace WebGame{
  namespace Message {
  class DataCache {
    typedef stlsoft::auto_buffer<char, 512> buffer_t ;
    public:
      class error : public std::runtime_error {
        public:
          error(const char* err) : runtime_error(err) {}
      } ;
      typedef std::shared_ptr<DataCache> pointer ;
      typedef std::shared_ptr<const DataCache> const_pointer ;
      void packToArray(void* buffer, size_t buffer_size) const {
        if(buffer_size < total_size()) throw error("pack array size is too small...") ;
#ifdef _WIN32
        memcpy_s(buffer, buffer_size, data(), total_size()) ;
#else
        std::memcpy(buffer, data(), total_size()) ;
#endif
      }
      const void* data() const { return static_cast<const void*>(m_buffer.data()) ;}
      size_t totalSize() const { return m_buffer.size() ;}
  
      //template<typename T>
      friend	const_pointer makeCached(DataBlock&) ;
      friend const_pointer makeCached(const DataBlock&) ;
      template<typename T, typename B>
        friend const_pointer makeCached(const T&, const B*) ;
      template<typename T, typename Identity>
        friend const_pointer makeCached(const T*, size_t, Identity id) ;
      template<typename T, typename Identity>
        friend const_pointer makeCached(const T&, size_t, Identity id) ;
      template<typename T, typename Identity>
        friend const_pointer makeCached(T&&, size_t, Identity id) ;

      template<typename T, typename Identity >
        friend const_pointer makeCached(size_t, Identity) ;

      friend const_pointer makeCached(const char*, size_t) ;


    private:
      DataCache() = delete ;
      DataCache(const DataCache& cache) = delete ;
      DataCache& operator = (const DataCache& cache) = delete ;
      DataCache(const char* cdata,
          size_t s) : m_buffer(s)
       {
         PANTHEIOS_ASSERT(s > 0) ;
        memcpy(data(), static_cast<const void*>(cdata),
            totalSize()) ;
      }

      DataCache(DataBlock& db) :
        m_buffer(db.totalSize()) {
          PANTHEIOS_ASSERT(db.totalSize() > 0) ;

          if(!db.packToArray(data(), total_size())) {
            throw error("could not create cache......") ;
          }
        }

      DataCache(const DataBlock& db) :
        m_buffer(db.total_size()) {
          PANTHEIOS_ASSERT(db.total_size() > 0) ;
          if(!db.packToArray(data(), total_size())) {
            throw error("could not create cache......") ;
          }
        }
      void* data() { return static_cast<void*>(m_buffer.data()) ;}

      template<typename T, typename Body>
        DataCache(const T& header, const Body* body) :
          m_buffer(totalMessageSize(header, body)) {
            pack_cache_message(header, body, data(), total_size()) ;
        }

      template<typename T, typename Identity>
        DataCache(T&& msg, size_t header_size, Identity id) : m_buffer(header_size +
            messageBodySize(std::forward<T>(msg))) {
          pack_cache_message(std::forward<T>(msg), data(), total_size(), id) ;
        }

      template<typename T, typename Identity>
        DataCache(size_t header_size, Identity id, T* t= 0) :
          m_buffer(header_size) {
            pack_EBO_body(data(), header_size, id, t) ;
          }
      buffer_t m_buffer ;
  } ;
  inline DataCache::const_pointer makeCached(DataBlock& db) {
    PANTHEIOS_ASSERT(db.total_size() > 0) ;
    return DataCache::const_pointer(new DataCache(db)) ;
  }
  inline DataCache::const_pointer makeCached(const DataBlock& db) {
    PANTHEIOS_ASSERT(db.total_size() > 0) ;
    return DataCache::const_pointer(new DataCache(db)) ;
  }

  template<typename T, typename B>
    DataCache::const_pointer makeCached(const T& header, const B* body = 0) {
      return DataCache::const_pointer(new DataCache(header, body)) ;
    }

  template<typename T, typename Identity>
    DataCache::const_pointer makeCached(T&& msg, size_t header_size, Identity id) {
      PANTHEIOS_ASSERT(header_size > 0) ;
      return DataCache::const_pointer(new DataCache(std::move(msg), header_size, id)) ;
    }

  template<typename T, typename Identity>
    DataCache::const_pointer makeCached(const T& msg, size_t header_size, Identity id) {
      PANTHEIOS_ASSERT(header_size > 0) ;
      return DataCache::const_pointer(new DataCache(msg, header_size, id)) ;
    }


  template<typename T, typename Identity>
    DataCache::const_pointer makeCached(size_t header_size, Identity id) {
      PANTHEIOS_ASSERT(header_size > 0) ;
      return DataCache::const_pointer(new DataCache(header_size, id, static_cast<T*>(0))) ;
    }

  inline DataCache::const_pointer makeCached(const char* data,
      size_t size) {
    PANTHEIOS_ASSERT(size > 0) ;
    PANTHEIOS_ASSERT(data) ;
    return DataCache::const_pointer(new DataCache(data, size)) ;
  }

  inline size_t binarySize(const DataCache::const_pointer& cache) {
    return cache->totalSize() ;
  }
  }

}


#endif
