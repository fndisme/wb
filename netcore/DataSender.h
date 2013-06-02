/*
 * =====================================================================================
 *
 *       Filename:  DataSender.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-9-1 14:21:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef FND_DATA_SENDER_H
#define FND_DATA_SENDER_H
#include <string>
#include <boost/noncopyable.hpp>
#include	<boost/variant.hpp>
#include	<pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "webgame/netcore/PoolBuffer.h"
#include "webgame/shared/identity_type.h"
#include	"webgame/message/DataCache.h"
#include "webgame/netcore/NetDataRecord.h"
#include "webgame/netcore/ForwardListBlocks.h"

namespace WebGame {
  namespace NetCore {
  template<typename NetConnection>
    class DataSender : boost::noncopyable {
      public:
        typedef typename NetConnection::data_type data_message_type ;
        typedef boost::variant<data_message_type, Message::DataCache::const_pointer> data_type ; 
        //typedef std::forward_list<data_type> BlocksType;
        typedef Message::DataCache::const_pointer cached_data_type ;
        typedef ForwardListBlocks<cached_data_type> BlocksType ;
        typedef DataSender<NetConnection> class_type ;

      public:
        void pack_send_message(const data_message_type& db) { 
          pack_send_message(makeCached(db)) ;
        }
        void pack_send_message(cached_data_type cache) {
          m_blocks.push(cache) ;
          prepare_message_to_net_pool(cache->totalSize()) ;
        }
        void pack_huge_message(const std::string&, const data_message_type&) ;
        bool prepare_data(bool send_huge) ;
        const char* data() const { return m_pool_buffer.data() ;}
        size_t size() const { return m_pool_buffer.size() ;}
        bool has_data() const { return m_blocks.has_data() ;}
        bool has_huge_data() const { return false ;}
        void extract_huge_message_to_stream() { }
        bool flush() ;
        bool is_traced() const { return m_blocks.is_traced();}
        void set_traced() { m_blocks.set_traced();}
        void unset_traced() { m_blocks.unset_traced(); }
        DataSender(size_t pool_size, size_t huge_block_size) ;
        ~DataSender() ;
      private:
        PoolBuffer<8194> m_pool_buffer ;
        BlocksType m_blocks ;
        size_t m_huge_block_size ;
        bool sop_block() ;
        bool sop_block_without_reset_size() ;
        bool try_sop_front_to_pool() ;
        bool can_pack_data_to_pool() const ;
    } ;
  }
}
#include "webgame/netcore/DataSender_inl.h"
#endif
