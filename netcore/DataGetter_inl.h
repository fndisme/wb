/*
 * =====================================================================================
 *
 *       Filename:  DataGetter_inl.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-3 13:49:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
// dont need header protect
template<typename NetConnection>
char* WebGame::NetCore::DataGetter<NetConnection>::data() { return m_pool_buffer.data() ;}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::start(SystemConnectionPointer conn) {
  pan::log_DEBUG("nc real start");
	boost::asio::async_read(m_socket,
			boost::asio::buffer(this->data(), this->headerSize()),
			makeCustomAllocHandler
			(m_receive_allocator,
			 m_strand.wrap(boost::bind(&class_type::handleReceiveDataHeader,
					 this,
           conn,
					 boost::asio::placeholders::error)))) ;
  pan::log_DEBUG("nc real start ok.") ;
}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::handleReceiveDataHeader(
    SystemConnectionPointer conn,
		boost::system::error_code const& error) {
  if(!conn) {
    return ;
  }

	if(error || !this->importHeader()) {
		if(conn) {
		pantheios::log_DEBUG("error rec", error.message(),
				pantheios::hex_ptr(conn.get())) ;
		conn->onError(error) ;
		} 
	} else if(this->bodySize() == 0) {
    pantheios::log_DEBUG("now body size = 0") ;
		this->handleReceiveDataHeader(conn, error) ;
	} else {
    boost::asio::async_read
			(m_socket,
			 boost::asio::buffer(this->data(), this->bodySize()),
			 makeCustomAllocHandler(m_receive_allocator,
				 m_strand.wrap
				 (boost::bind(&class_type::handleReceiveDataBody,
											this,
                      conn,
											boost::asio::placeholders::error)))) ;
	}
}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::handleReceiveDataBody(
    SystemConnectionPointer conn,
    boost::system::error_code const& error) {
  if(error || !this->importBody()) {

    if(conn.get()) {
      pantheios::log_WARNING("receive data body error") ;
      conn->onError(error) ;
    } 
  } else {

    if(!conn.get()) {
      pantheios::log_WARNING("conn has gone....") ;
      return ;
    } 

    dealMessage(conn) ;
    boost::asio::async_read(m_socket,
        boost::asio::buffer(this->data(),
          this->headerSize()),
        makeCustomAllocHandler
        (m_receive_allocator,
         m_strand.wrap(boost::bind(&class_type::handleReceiveDataHeader,
             this,
             conn,
             boost::asio::placeholders::error)))) ;
  }
}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::initOrUninitDealMessage(
		const std::false_type&,
		net_connection_pointer ) {
	m_blocks.push_back(m_current_block) ;
}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::initOrUninitDealMessage(const std::true_type&,
		net_connection_pointer nc) {
	messageDealer(std::cref(m_current_block), nc) ;
}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::setMaxBodySize(size_t size)
{ m_pool_buffer.resetCapacity(size) ;}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::dealMessage(net_connection_pointer nc) {
	typedef std::is_void<ActiveManageMessageType> ActiveType ;
	initOrUninitDealMessage(ActiveType(), nc) ;
}

template<typename NetConnection>
bool WebGame::NetCore::DataGetter<NetConnection>::importBody() {
  return m_current_block.importBodyFromArray(m_pool_buffer.data(),
			bodySize(),
            m_decoder) ;
}

template<typename NetConnection>
bool WebGame::NetCore::DataGetter<NetConnection>::importHeader() {
  if(m_current_block.importHeaderFromArray(m_pool_buffer.data(),
        headerSize())) {
    if((!m_can_change_pool_size) && m_pool_buffer.capacity() < bodySize()) return false ;
    m_pool_buffer.resetCapacity(bodySize()) ;
    return true ;
  } else {
    return false ;
  }
}

template<typename NetConnection>
WebGame::NetCore::DataGetter<NetConnection>::DataGetter(
		std::shared_ptr<NetConnection> conn,
		size_t buffer_size,
		bool can_change_pool_size) :
    messageDealer(dummy<block_type, NetConnection>),
	m_socket(conn->socket()),
	m_strand(conn->readStrand()),
    m_decoder(conn->decoder()),
    m_can_change_pool_size(can_change_pool_size),
	m_pool_buffer(buffer_size),
    m_blocks(),
    m_current_block(),
    m_receive_allocator() {}

template<typename NetConnection>
void WebGame::NetCore::DataGetter<NetConnection>::popHeadStockMessage()
{ m_blocks.pop_front() ;}

template<typename NetConnection>
size_t WebGame::NetCore::DataGetter<NetConnection>::headerSize() const
{ return m_current_block.headerSize() ;}

template<typename NetConnection>
bool WebGame::NetCore::DataGetter<NetConnection>::receiveAsyncMessage
(typename WebGame::NetCore::DataGetter<NetConnection>::block_type& db) {
	if (!this->has_stock_message()) return false ;
	db = std::move(this->headMessage()) ;
	popHeadStockMessage() ;
	return true ;
}

template<typename NetConnection>
size_t WebGame::NetCore::DataGetter<NetConnection>::bodySize() const
{ return m_current_block.bodySize() ;}

template<typename NetConnection>
const typename WebGame::NetCore::DataGetter<NetConnection>::block_type&
WebGame::NetCore::DataGetter<NetConnection>::headMessage() const { return m_blocks.front() ;}

template<typename NetConnection>
bool WebGame::NetCore::DataGetter<NetConnection>::hasStockMessage() const
{ return !m_blocks.empty() ;}
