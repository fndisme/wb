/*
 * =====================================================================================
 *
 *       Filename:  ForwardListBlocks.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年01月09日 16时20分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_NETCORE_FORWARDLISTBLOCKS_H
#define FND_WEBGAME_NETCORE_FORWARDLISTBLOCKS_H
#include <forward_list>
#include <folly/Optional.h>
namespace WebGame {
  template<typename D>
    class ForwardListBlocks {
      public:
        typedef D data_type ;
        typedef std::forward_list<data_type> BlocksType;
        typedef folly::Optional<data_type> OptionalValue ;

        bool has_data() const { return !m_blocks.empty() ;}

        void push(const data_type& db) {
          m_blocks.insert_after(m_pos, db) ;
          ++m_pos ;
        }

        OptionalValue pop_front() {
          if(!has_data()) return OptionalValue() ;

          data_type d = std::move(m_blocks.front()) ;
          m_blocks.pop_front() ;
          if(!has_data()) m_pos = m_blocks.before_begin() ;

          return d ;
        }

        size_t front_value_size() const {
          return binary_size(m_blocks.front()) ;
        }

        ForwardListBlocks() {
          m_pos = m_blocks.before_begin() ;
        }

        size_t size() const { // very slow!!!!!!
          return std::distance(m_blocks.begin(), m_blocks.end()) ;
        }

        bool is_traced() const { return m_is_sending ;}
        void set_traced() { m_is_sending = true ;}
        void unset_traced() { m_is_sending = false ;}


      private:
        BlocksType m_blocks ;
        typename BlocksType::iterator m_pos ;
        bool m_is_sending = false ;

    } ;
}
#endif

