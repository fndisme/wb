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
char* WebGame::Net::DataGetter<NetConnection>::data() { return m_pool_buffer.data() ;}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::start(SystemConnectionPointer conn) {
  pan::log_DEBUG("nc real start");
	boost::asio::async_read(m_socket,
			boost::asio::buffer(this->data(), this->header_size()),
			make_custom_alloc_handler
			(m_receive_allocator,
			 m_strand.wrap(boost::bind(&class_type::handleReceiveDataHeader,
					 this,
           conn,
					 boost::asio::placeholders::error)))) ;
  pan::log_DEBUG("nc real start ok.") ;
}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::handleReceiveDataHeader(
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
	} else if(this->body_size() == 0) {
    pantheios::log_DEBUG("now body size = 0") ;
		this->handleReceiveDataHeader(conn, error) ;
	} else {
    boost::asio::async_read
			(m_socket,
			 boost::asio::buffer(this->data(), this->body_size()),
			 make_custom_alloc_handler(m_receive_allocator,
				 m_strand.wrap
				 (boost::bind(&class_type::handleReceiveDataBody,
											this,
                      conn,
											boost::asio::placeholders::error)))) ;
	}
}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::handleReceiveDataBody(
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
          this->header_size()),
        make_custom_alloc_handler
        (m_receive_allocator,
         m_strand.wrap(boost::bind(&class_type::handleReceiveDataHeader,
             this,
             conn,
             boost::asio::placeholders::error)))) ;
  }
}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::initOrUninitDealMessage(
		const std::false_type&,
		net_connection_pointer ) {
	m_blocks.push_back(m_current_block) ;
}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::initOrUninitDealMessage(const std::true_type&,
		net_connection_pointer nc) {
	messageDealer(std::cref(m_current_block), nc) ;
}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::set_max_body_size(size_t size)
{ m_pool_buffer.resetCapacity(size) ;}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::dealMessage(net_connection_pointer nc) {
	typedef std::is_void<ActiveManageMessageType> ActiveType ;
	initOrUninitDealMessage(ActiveType(), nc) ;
}

template<typename NetConnection>
bool WebGame::Net::DataGetter<NetConnection>::importBody() {
  return m_current_block.import_body_from_array(m_pool_buffer.data(),
			bodySize()) ;
}

template<typename NetConnection>
bool WebGame::Net::DataGetter<NetConnection>::importHeader() {
  if(m_current_block.import_header_from_array(m_pool_buffer.data(),
        header_size())) {
    if((!m_can_change_pool_size) && m_pool_buffer.capacity() < body_size()) return false ;
    m_pool_buffer.resetCapacity(body_size()) ;
    return true ;
  } else {
    return false ;
  }
}

template<typename NetConnection>
WebGame::Net::DataGetter<NetConnection>::DataGetter(
		std::shared_ptr<NetConnection> conn,
		size_t buffer_size,
		bool can_change_pool_size) :
  messageDealer(dummy<block_type, NetConnection>),
	m_io_service(conn->get_io_service()),
	m_socket(conn->socket()),
	m_strand(conn->get_strand()),
  m_can_change_pool_size(can_change_pool_size),
	m_pool_buffer(buffer_size),
  m_blocks{},
  m_current_block{},
  m_receive_allocator{} {}

template<typename NetConnection>
void WebGame::Net::DataGetter<NetConnection>::popHeadStockMessage()
{ m_blocks.pop_front() ;}

template<typename NetConnection>
size_t WebGame::Net::DataGetter<NetConnection>::headerSize() const
{ return m_current_block.header_size() ;}

template<typename NetConnection>
bool WebGame::Net::DataGetter<NetConnection>::receiveAsyncMessage
(typename WebGame::DataGetter<NetConnection>::block_type& db) {
	if (!this->has_stock_message()) return false ;
	db = std::move(this->head_message()) ;
	popHeadStockMessage() ;
	return true ;
}

template<typename NetConnection>
size_t WebGame::Net::DataGetter<NetConnection>::bodySize() const
{ return m_current_block.body_size() ;}

template<typename NetConnection>
const typename WebGame::Net::DataGetter<NetConnection>::block_type&
WebGame::DataGetter<NetConnection>::headMesage() const { return m_blocks.front() ;}

template<typename NetConnection>
bool WebGame::Net::DataGetter<NetConnection>::hasStockMessage() const
{ return !m_blocks.empty() ;}
