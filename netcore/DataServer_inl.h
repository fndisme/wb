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
// not need protected

template<typename NetConnection>
bool WebGame::DataSender<NetConnection>::prepare_data(bool send_huge) {
	auto ok = has_data() ;
	if(ok) {
		//m_blocks.front().sync() ;
		auto msg_size = 
			boost::apply_visitor(data_size_visitor(), m_blocks.front()) ; //.total_size() ;
		m_pool_buffer.reset_capacity(msg_size) ;
		boost::apply_visitor(pack_data_visitor(m_pool_buffer.append_data_address(), msg_size), 
				m_blocks.front());
		//m_blocks.front().pack_to_array(m_pool_buffer.data() + m_pool_buffer.size(),
		//		msg_size) ;
		m_pool_buffer.append(msg_size) ;
		m_blocks.pop_front() ;
		if(send_huge) {
			extract_huge_message_to_stream() ;
			while(can_pack_data_to_pool()) {
				sop_front_to_pool() ;
				extract_huge_message_to_stream() ;
			}
		} else {
			while(can_pack_data_to_pool()) sop_front_to_pool() ;
		}
	}
	return ok ;
}

template<typename NetConnection>
bool WebGame::DataSender<NetConnection>::flush() {
	if(!is_pooled()) {
		set_unpooled() ;
		if(!has_data()) {
			extract_huge_message_to_stream() ;
		}
		return has_data() ;
	}

	if(has_data()) {
		return false ;
	} else {
		extract_huge_message_to_stream() ;
		return has_data() ;
	}
}

template<typename NetConnection>
void WebGame::DataSender<NetConnection>::sop_front_to_pool() {
	auto msg_size = boost::apply_visitor(data_size_visitor(),m_blocks.front()) ;
	boost::apply_visitor(pack_data_visitor(m_pool_buffer.append_data_address(),
				msg_size), m_blocks.front()) ;
	m_blocks.pop_front() ;
	m_pool_buffer.append(msg_size) ;
}

template<typename NetConnection>
bool WebGame::DataSender<NetConnection>::can_pack_data_to_pool() const {
	return (!m_blocks.empty()) && 
		(boost::apply_visitor(data_size_visitor(), m_blocks.front()) + 
		 m_pool_buffer.size()) <= m_pool_buffer.capacity() ; 
}

template<typename NetConnection>
WebGame::DataSender<NetConnection>::DataSender(size_t pool_size, size_t huge_block_size) 
	: m_pool_buffer(pool_size),
	m_huge_block_size(huge_block_size),
	m_is_sending(false)	{}

