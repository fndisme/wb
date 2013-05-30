/*
 * =====================================================================================
 *
 *       Filename:  DataSender_inl.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-4 10:07:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */

template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::prepare_data(bool send_huge) {
  if(sop_block()) {
		if(send_huge) {
			extract_huge_message_to_stream() ;
			while(try_sop_front_to_pool()) {
				extract_huge_message_to_stream() ;
			}
		} else {
			while(try_sop_front_to_pool()) ;
		}
    return true ;
  }
  return false ;
}

template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::sop_block_without_reset_size() {
 auto optional_cache = m_blocks.pop_front() ;
	if(optional_cache) {
    auto cache = optional_cache.value() ;
    auto msg_size = binarySize(cache) ;
    cache->packToArray(m_pool_buffer.appendDataAddress(), msg_size) ;
    m_pool_buffer.append(msg_size) ;
    add_record_to_net_poll() ;
    return true ;
  }
  return false ;
}


template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::sop_block() {
 auto optional_cache = m_blocks.pop_front() ;
	if(optional_cache) {
    auto cache = optional_cache.value() ;
    auto msg_size = binarySize(cache) ;
    m_pool_buffer.resetCapacity(msg_size) ;
    cache->packToArray(m_pool_buffer.appendDataAddress(), msg_size) ;
    m_pool_buffer.append(msg_size) ;
    add_record_to_net_poll() ;
    return true ;
  }
  return false ;
}



template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::try_sop_front_to_pool() {
  return can_pack_data_to_pool() && sop_block_without_reset_size() ; 
}

template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::flush() {

	if(has_data()) {
		return false ;
	} else {
		extract_huge_message_to_stream() ;
		return has_data() ;
	}
}

template<typename NetConnection>
WebGame::NetCore::DataSender<NetConnection>::~DataSender() {
  add_record_to_net_poll(m_blocks.size()) ;
}

template<typename NetConnection>
bool WebGame::NetCore::DataSender<NetConnection>::can_pack_data_to_pool() const {
	return m_blocks.has_data() && 
		(m_blocks.front_value_size() + 
		 m_pool_buffer.size()) <= m_pool_buffer.capacity() ; 
}

	template<typename NetConnection>
WebGame::NetCore::DataSender<NetConnection>::DataSender(size_t pool_size, size_t huge_block_size) 
	: m_pool_buffer(pool_size),
  m_blocks{},
	m_huge_block_size(huge_block_size) {
  }

template<typename NetConnection>
void WebGame::NetCore::DataSender<NetConnection>::pack_huge_message(const std::string& name,
		const data_message_type&) {
	/*
		 auto group = Fnd::create_mini_block_group(name,
		 m_huge_block_size,
		 db) ;
		 m_huge_messages.push_back(std::move(group)) ;
		 */
}
