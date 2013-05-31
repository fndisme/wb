/*
 * =====================================================================================
 *
 *       Filename:  tiny_finder.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2010-11-24 13:39:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  Artcoding, Shanghai, China
 *
 * =====================================================================================
 */
#ifndef UTILITY_FND_TINY_FINDER_H
#define UTILITY_FND_TINY_FINDER_H
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <boost/noncopyable.hpp>
namespace WebGame {
namespace Utility {
template<typename K, typename V>
  class TinyFinder : boost::noncopyable {
    public:
      typedef K key_type ;
      typedef V search_type ;
      typedef std::unordered_map<K,V> container_type ;
      typedef typename container_type::mapped_type mapped_type ;
      typedef TinyFinder<K, V> class_type ;
      void insert(K k, const V& v) {
        assert(isDirty()) ;
        m_values[k] = v ;
      }

      void insert(K k, V&& v) {
        assert(isDirty()) ;
        m_values[k] = std::move(v) ;
      }

      void makeFinal() {
        assert(isDirty()) ;
        m_values.rehash(static_cast<size_t>(m_values.size() / 1.1f)) ;
        m_dirty = false ;
      }

      const mapped_type& value(K key) const {
        assert(!isDirty()) ;
        return m_values.at(key) ;
      }

      bool hasValue(K key) const {
        assert(!isDirty()) ;
        return m_values.count(key) == 1 ;
      }

      TinyFinder() : 
        m_values(),
        m_dirty(true){}
      bool isDirty() const { return m_dirty ;}
    private:
      container_type m_values ;
      bool m_dirty ;
      //TinyFinder(const class_type&) = delete ;
      //TinyFinder& operator = (const class_type&) = delete ;
  } ;
}
}
#endif

