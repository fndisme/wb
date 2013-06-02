/*
 * =====================================================================================
 *
 *       Filename:  net_acceptor_inl.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-11-3 16:01:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
// not proctected

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::asyncConnect() {
	m_current_conection.reset(
      new net_connection_type(
          m_readStrand.get_io_service(),
          m_readStrand,
          m_writeStrand, 
          m_decoder)) ;
	m_acceptor.async_accept(m_current_conection->socket(),
			m_readStrand.wrap(
				boost::bind(&class_type::handleNewConnection,
					this,
					boost::asio::placeholders::error))) ;
}


template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::start(
		const NetAcceptorProperty& prop,
		const NetAcceptorOption& option) {
	using boost::asio::ip::tcp ;
	tcp::endpoint endpoint(tcp::v4(), m_port) ;
	m_acceptor.close() ;
	m_acceptor.open(endpoint.protocol()) ;
	m_acceptor.set_option(tcp::acceptor::reuse_address(option.IsAddressReused)) ;
	m_acceptor.set_option(boost::asio::socket_base::send_buffer_size(option.SendBufferSize)) ;
	m_acceptor.set_option(boost::asio::socket_base::receive_buffer_size(option.ReceiveBufferSize)) ;
	checkCallback = prop.HandleConnect ;
	successedCallback = prop.HandleConnectSuccessed ;
	errorCallback = prop.HandleDataError ;
	messageCallback = prop.HandleData ;
	m_data_getter_cache_size = option.GetterCacheSize ;
	m_acceptor.bind(endpoint) ;
	m_acceptor.listen() ;
}

template<typename NetConnection>
WebGame::NetCore::Acceptor<NetConnection>::Acceptor(
        boost::asio::strand& readStrand,
        boost::asio::strand& writeStrand,
        const DecoderType& decoder,
        int port) :
    m_readStrand(readStrand),
    m_writeStrand(writeStrand),
    m_decoder(decoder),
    m_connections(),
    m_current_conection(),
    messageCallback(),
    errorCallback(),
    checkCallback(),
    successedCallback(),
    m_port(port),
    m_acceptor(readStrand.get_io_service()),
    m_data_getter_cache_size(0){ }

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::removeConnection(const boost::system::error_code& e,
		nc_pointer_type nc){

	pantheios::log_DEBUG("because:", e.message(),
			" socket broken") ;
	m_connections.erase(nc) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::doPostMessageExcept(
		const data_type& db,
		nc_pointer_type nc) const {
  Message::DataCache::const_pointer cache = makeCached(db) ;
	doPostMessageExcept(cache) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::doPostMessageExcept(
		Message::DataCache::const_pointer db,
		nc_pointer_type nc) const {
	std::for_each(m_connections.begin(),
			m_connections.end(),
			[&db, nc](nc_pointer_type n)
			{if(n != nc) n->sendAsyncMessage(db) ;}) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::doPostMessage(
		const data_type& db) const {
  Message::DataCache::const_pointer cache = makeCached(db) ;
	doPostMessage(cache) ;
}
template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::doPostMessage(
		Message::DataCache::const_pointer db) const {
	std::for_each(m_connections.begin(),
			m_connections.end(),
			[&db](nc_pointer_type nc){nc->sendAsyncMessage(db) ;}
			) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::handleNewConnection(
		const boost::system::error_code& error) {
	if(checkCallback(m_current_conection, error)) {
		pantheios::log_DEBUG("socket connect successed:",
				net_connection_type::describeRemoteConnection(m_current_conection)) ;
		m_current_conection->handleError.connect
			(boost::bind(&class_type::removeConnection,
									 this, _1, _2)) ;
		m_connections.insert(m_current_conection) ;
		typename net_connection_type::data_getter_pointer
			p(new typename net_connection_type::data_getter_type(m_current_conection, m_data_getter_cache_size)) ;

		p->messageDealer = messageCallback;
		m_current_conection->handleError.connect(errorCallback) ;
		m_current_conection->resetGetter(std::move(p)) ;
    pan::log_DEBUG("BF call connect successed") ;
		successedCallback(m_current_conection) ;
    pan::log_DEBUG("call successed ok", pan::i(m_current_conection.use_count())) ;
		asyncConnect() ;
    pan::log_DEBUG("call next round") ;
	} else {
		m_current_conection->onError(error) ;
		pantheios::log_ERROR("new client socket error: ",
				net_connection_type::describeRemoteConnection(m_current_conection)) ;
	}
}

/* static */
template<typename NetConnection>
typename WebGame::NetCore::Acceptor<NetConnection>::pointer
WebGame::NetCore::Acceptor<NetConnection>::create(
        boost::asio::strand& readStrand,
    boost::asio::strand& writeStrand,
    DecoderType const& decoder,
		int port, const NetAcceptorProperty& p,
		const NetAcceptorOption& option) {
	pointer acceptor(new class_type(readStrand, writeStrand, decoder, port)) ;
	acceptor->start(p, option) ;
	return acceptor ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::postMessage(const data_type& db) const {
	m_writeStrand.post(boost::bind(&class_type::doPostMessage,
				this,
				db)) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::postMessage(Message::DataCache::const_pointer db) const {
	m_writeStrand.post(boost::bind(&class_type::doPostMessage,
				this,
				db)) ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::postMessageExcept(const data_type& db,
		nc_pointer_type nc) const {
	m_writeStrand.post(boost::bind(&class_type::doPostMessageExcept,
					this,
					db,
					nc)) ;

}
template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::postMessageExcept(Message::DataCache::const_pointer db,
		nc_pointer_type nc) const {
	m_writeStrand.post(boost::bind(&class_type::doPostMessageExcept,
					this,
					db,
					nc)) ;

}

template<typename NetConnection>
int WebGame::NetCore::Acceptor<NetConnection>::receiveBufferSize() {
	boost::asio::socket_base::receive_buffer_size option;
	m_acceptor.get_option(option);
	return option.value();
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::setSendBufferSize(int newsize) {
	boost::asio::socket_base::send_buffer_size option(newsize);
	m_acceptor.set_option(option);
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::setReceiveBufferSize(int newsize) {
	boost::asio::socket_base::receive_buffer_size option(newsize);
	m_acceptor.set_option(option);
}

template<typename NetConnection>
size_t WebGame::NetCore::Acceptor<NetConnection>::connectionSize() const
{ return m_connections.size() ;}

template<typename NetConnection>
int WebGame::NetCore::Acceptor<NetConnection>::sendBufferSize() {
	boost::asio::socket_base::send_buffer_size option;
	m_acceptor.get_option(option);
	return option.value();
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::stopAll() {
	auto conns(std::move(m_connections)) ;
	std::for_each(conns.begin(),
			conns.end(),
			[](nc_pointer_type nc) {nc->onError() ;}
			) ;
  stopAccpetNewConnection() ;
}

template<typename NetConnection>
void WebGame::NetCore::Acceptor<NetConnection>::stopAccpetNewConnection() {
  // MAYBE FIXME
  // just do nothing for m_current_socket......?
//	if(m_current_conection) {
//		m_current_conection->on_error() ;
//	}
	m_acceptor.close() ;

}


