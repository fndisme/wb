/*
 * =====================================================================================
 *
 *       Filename:  net_connection_inl.h
 *
 *
 * =====================================================================================
 */
// not protected

/*static */
template<typename ConnectionTraits>
std::string WebGame::NetCore::Connection<ConnectionTraits>::describeRemoteConnection(
		const_pointer nc) {
	return describeRemoteConnection(*nc) ;
}


template<typename ConnectionTraits>
std::string WebGame::NetCore::Connection<ConnectionTraits>::describeRemoteConnection(
		const class_type& nc) {
	std::string sink ;
  try {
	if(nc.isOpen())
		fastformat::fmt(sink, "{0}:{1}", nc.describeRemoteAddress(), nc.remote_port()) ;
	else sink = "connection is not valid" ;
  } catch (const boost::system::system_error& error) {
    sink = "Socket Error : " ;
    sink += error.what() ;
  }
	return sink ;
}

template<typename ConnectionTraits>
WebGame::NetCore::Connection<ConnectionTraits>::Connection(
		boost::asio::io_service& io_service,
    boost::asio::strand& readStrand,
    boost::asio::strand& writeStrand,
		std::shared_ptr<data_getter_type> getter) :
  asyncConnect(),
  handleError(),
	m_io_service(io_service),
	m_readStrand(readStrand),
  m_writeStrand(writeStrand),
	m_need_handle_error(true),
  m_sender(huge_message_mini_size, huge_message_mini_size),
  m_getter(getter),
	m_socket(io_service),
	m_close_option(normal),
  m_send_allocator(),
  m_heart_state(HB_STRONG) {
}

template<typename ConnectionTraits>
typename WebGame::NetCore::Connection<ConnectionTraits>::pointer
WebGame::NetCore::Connection<ConnectionTraits>::createAsyncConnection(
		boost::asio::io_service& io_service,
    boost::asio::strand& readStrand,
    boost::asio::strand& writeStrand,
		const ConnectionOption& option,
		const ConnectionProperty<class_type>& property) {

	pointer new_connect(new class_type(io_service, readStrand, writeStrand)) ; //, std::move(getter))) ;
	data_getter_pointer getter(new data_getter_type(new_connect, option.GetterBufferSize)) ;
	new_connect->resetGetter(std::move(getter)) ;
	getter->messageDealer = property.HandleData ;
	new_connect->handleError.connect(property.HandleError) ;
	new_connect->asyncConnect = property.HandleOk ;
	new_connect->startAsyncConnect(option.ServerAddress, option.Port) ;
	return new_connect ;
}

template<typename ConnectionTraits>
typename WebGame::NetCore::Connection<ConnectionTraits>::pointer
WebGame::NetCore::Connection<ConnectionTraits>::createSyncConnection(
		boost::asio::io_service& io_service,
    boost::asio::strand& readStrand,
    boost::asio::strand& writeStrand,
		const ConnectionOption& option,
		const ConnectionProperty<class_type>& property) {

	pointer new_connect(new class_type(io_service, readStrand, writeStrand)) ; //, std::move(getter))) ;
	data_getter_pointer getter(new data_getter_type(new_connect, option.GetterBufferSize)) ;
	new_connect->resetGetter(std::move(getter)) ;
	getter->message_dealer = property.HandleData ;
	new_connect->handleError.connect(property.HandleError) ;

	boost::system::error_code error = boost::asio::error::host_not_found ;
	new_connect->startAsyncConnect(option.ServerAddress, option.Port, error) ;
	if (error) {
		new_connect.reset() ;
	}
	return new_connect ;
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::sendAsyncMessage(const data_type& db) {
  m_sender.pack_send_message(db) ;
  if (!m_sender.is_traced()) {
    realSendInformation() ;
  }

}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::sendAsyncMessage(
    typename Connection<ConnectionTraits>::IdentityType pid,
		const data_type& db) {
	data_type db2(db) ;
	db2.set_header_id(pid) ;
	sendAsyncMessage(db2) ;
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::sendAsyncMessage(Message::DataCache::const_pointer cache) {
	m_sender.pack_send_message(cache) ;
	if (!m_sender.is_traced()) {
		realSendInformation() ;
	}

}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::handleSendData(
		const boost::system::error_code& error) {
	if (error) {
		onError(error) ;
		return ;
	} 
	typedef std::is_void<ActiveSendHugeData> SendHugeOption ;
	if(m_sender.prepare_data(SendHugeOption::value)) {
		boost::asio::async_write(m_socket,
				boost::asio::buffer
				(m_sender.data(), m_sender.size()),
				makeCustomAllocHandler
				(m_send_allocator,
				 m_writeStrand.wrap(boost::bind(&class_type::handleSendData,
						 this->shared_from_this(),
						 boost::asio::placeholders::error)))) ;
	} else if(m_close_option == send_all_message_and_quit) {
		onError() ;
	} else {
		m_sender.unset_traced() ;
	}
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::handleAsyncConnect(const boost::system::error_code& error,
		boost::asio::ip::tcp::resolver::iterator iterator){
	using boost::asio::ip::tcp ;
	if (!error) {
		typedef std::is_void<NotDelayMessageType> DelayOptionType ;
		m_socket.set_option(tcp::no_delay((DelayOptionType::value))) ;
		start() ;
		asyncConnect(this->shared_from_this()) ;

	} else if (iterator != tcp::resolver::iterator()) {
		m_socket.close() ;
		tcp::endpoint endpoint = *iterator ;
		m_socket.async_connect(endpoint,
				m_readStrand.wrap
				(boost::bind
				 (&class_type::handleAsyncConnect,
					this->shared_from_this(),
					boost::asio::placeholders::error,
					iterator++))) ;

	} else {
		onError(error) ;
	}
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::disconnect(const boost::system::error_code& error) {
  if(!error) { // connection stop by active
    boost::system::error_code error2 ;
    if(m_close_option == send_all_message_and_quit)
      m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, error2) ;
    else 
      m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error2) ;
    if(error2) {
      pantheios::log_WARNING("shut down error ", error2.message()) ;
    }
  }
  handleError(error, this->shared_from_this()) ;
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::realSendInformation() {
	m_sender.set_traced() ;

	typedef std::is_void<ActiveSendHugeData> SendHugeOption ;
	m_sender.prepare_data(SendHugeOption::value) ;
	boost::asio::async_write
		(m_socket,
		 boost::asio::buffer(m_sender.data(), m_sender.size()),
		 makeCustomAllocHandler
		 (m_send_allocator,
			m_writeStrand.wrap
			(boost::bind(&class_type::handleSendData,
									 this->shared_from_this(),
									 boost::asio::placeholders::error))) ) ;

}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::startAsyncConnect(const std::string& address,
    const std::string& port) {
  using boost::asio::ip::tcp ;
  tcp::resolver resolver(m_io_service) ;
  tcp::resolver::query query(address, port) ;
  tcp::resolver::iterator iterator = resolver.resolve(query) ;
  m_socket.close() ;
  tcp::endpoint endpoint = *iterator ;
  m_socket.async_connect(endpoint,
      m_readStrand.wrap
      (boost::bind(&class_type::handleAsyncConnect,
                   this->shared_from_this(),
                   boost::asio::placeholders::error,
                   iterator++))) ;
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::startAsyncConnect(const std::string& address,
		const std::string& port,
		boost::system::error_code& error) {
	using boost::asio::ip::tcp ;
	tcp::resolver resolver(m_io_service) ;
	error = boost::asio::error::host_not_found ;
	tcp::resolver::query query(address, port) ;
	tcp::resolver::iterator iterator = resolver.resolve(query) ;
	tcp::resolver::iterator end ;
	while (error && iterator != end) {
		m_socket.close() ;
		m_socket.connect(*iterator++, error) ;
	}
	if (!error) {
		typedef std::is_void<NotDelayMessageType> NotDelayOptionType ;
		m_socket.set_option(tcp::no_delay(NotDelayOptionType::value)) ;
	}
}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::flush() {
	//m_io_service.post
  m_io_service.dispatch
		(makeCustomAllocHandler(m_send_allocator,
                               m_writeStrand.wrap(
															 boost::bind(&class_type::doFlush,
																 this->shared_from_this())))) ;

}

template<typename ConnectionTraits>
void WebGame::NetCore::Connection<ConnectionTraits>::setCloseOption(CloseOption option){
	m_close_option = option ;
	if(m_close_option == send_all_message_and_quit) {
		shutdown(boost::asio::ip::tcp::socket::shutdown_receive) ;
	}
}

template<typename ConnectionTraits>
bool WebGame::NetCore::Connection<ConnectionTraits>::receiveAsyncMessage(data_type& db) {
	return m_getter->receive_async_message(db) ;
}



