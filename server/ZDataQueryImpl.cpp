/*
 * =====================================================================================
 *
 *       Filename:  ZDataQueryImpl.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-18 15:17:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */

#include "webgame/server/ZDataQueryImpl.h"
#include <algorithm>
#include <boost/bind.hpp>
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "webgame/utility/PageParser.h"
#include "webgame/server/ZPollInManager.h"
//#include "webgame/server/ZSocketUtility.h"
#include "webgame/message/shims/DataBlock.h"
#include <iostream>


#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::ZDataQuery::Impl

namespace
{
const std::string Net("ZNet") ;
const std::string QueryerName("QueryerName") ;
const std::string DefaultName("") ;
const std::string ReceiveConnection("ReceiveConnection") ;
const std::string SenderConnection("SenderConnection") ;
const std::string DefaultReceiveConnection("tcp://localhost:5556") ;
}

void THIS_CLASS::init(const std::string& initfile) {
    using Utility::PageParser;
    PageParser pp(initfile) ;

    std::string receiver_address(pp.get(Net, ReceiveConnection, DefaultReceiveConnection)) ;
    m_name = pp.get(Net, QueryerName, DefaultName) ;
    if(m_name.empty()) throw std::runtime_error("Query Player name should not empty.") ;
    //m_socket->setsockopt(XS_IDENTITY, m_name.data(), m_name.size()) ;
    m_socket->setsockopt(QSocketTratis::optionIdentity(), m_name.data(), m_name.size()) ;
    m_socket->connect(receiver_address.c_str()) ;
    int linger = 0 ;

    m_socket->setsockopt(QSocketTratis::optionLinger(), &linger, sizeof linger) ;
}

THIS_CLASS::~Impl() {}

THIS_CLASS::Impl(QSocketTratis::context_t& ctx,
    boost::asio::strand& strand,
    const std::string& info) :
    m_strand(strand),
    m_handlers(),
    m_translaters(),
    m_send_messages(),
    m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::typeDealer())),
    m_name() {
    init(info) ;
}


void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
    mgr->registerWriteActor(boost::bind(&THIS_CLASS::sendQuery, this)) ;
    mgr->registerReadActor(*m_socket, boost::bind(&THIS_CLASS::dealMessage, this)) ;
}

void THIS_CLASS::dealMessage() {
    auto deal_single_msg = [this](std::shared_ptr<data_type> db) {
        m_handlers.dispatch(db->messageType(), *db) ;
    } ;

    QSocketTratis::absorbAndDispatchMessage<data_type>(*m_socket, deal_single_msg, m_strand) ;
}

void THIS_CLASS::sendQuery() {
    if(m_send_messages.empty()) return ;
    QSocketTratis::sendAllGroupMessage(m_send_messages, *m_socket) ;
}


THIS_CLASS::data_type THIS_CLASS::translateMessage(int hint,
    const THIS_CLASS::data_type& db) const {
    data_type trans ;
    m_translaters.dispatch(db.messageType(),
        std::make_tuple(hint, std::cref(db), std::ref(trans))) ;
    return trans ;
}

#undef THIS_CLASS
