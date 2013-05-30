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
#include <algorithm>
#include <boost/bind.hpp>
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "page_file_parser.h"
#include "ZDataQueryImpl.h"
#include "ZPollInManager.h"
#include "ZSocketUtility.h"
#include "shims/data_block.h"
#include <iostream>


#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::ZDataQuery::Impl

namespace
{
const std::string Net("ZNet") ;
const std::string QueryerName("QueryerName") ;
const std::string DefaultName("") ;
const std::string ReceiveConnection("ReceiveConnection") ;
const std::string SenderConnection("SenderConnection") ;
const std::string DefaultReceiveConnection("tcp://localhost:5556") ;
}

void THIS_CLASS::init(const std::string& initfile)
{
    using Utility::page_parser ;
    page_parser pp(initfile) ;

    std::string receiver_address(pp.get(Net, ReceiveConnection, DefaultReceiveConnection)) ;
    m_name = pp.get(Net, QueryerName, DefaultName) ;
    if(m_name.empty()) throw std::runtime_error("Query Player name should not empty.") ;
    //m_socket->setsockopt(XS_IDENTITY, m_name.data(), m_name.size()) ;
    m_socket->setsockopt(QSocketTratis::option_identity(), m_name.data(), m_name.size()) ;
    m_socket->connect(receiver_address.c_str()) ;
    int linger = 0 ;

    m_socket->setsockopt(QSocketTratis::option_linger(), &linger, sizeof linger) ;
}

THIS_CLASS::~Impl() {}

THIS_CLASS::Impl(QSocketTratis::context_t& ctx, const std::string& info) :
    m_handlers(),
    m_translaters(),
    m_send_messages {},
                //m_socket(new socket_t(ctx, XS_DEALER)),

                m_socket(new QSocketTratis::socket_t(ctx, QSocketTratis::type_dealer())),
                m_name()
{
    init(info) ;
}


void THIS_CLASS::bind_to_poll_manager(WebGame::ZPollInManager* mgr)
{
    mgr->register_absolute_actor(boost::bind(&THIS_CLASS::send_query, this)) ;
    mgr->register_actor(*m_socket, boost::bind(&THIS_CLASS::deal_message, this)) ;
}

void THIS_CLASS::deal_message()
{
    auto deal_single_msg = [this](const Fnd::data_block& db) {
        m_handlers.deal_with_message(db.message_type(), std::cref(db)) ;
    } ;

    //xs_absorb_and_handle_message<Fnd::data_block>(*m_socket, deal_single_msg) ;
    //
    QSocketTratis::absorb_and_handle_message<Fnd::data_block>(*m_socket, deal_single_msg) ;
}

void THIS_CLASS::send_query()
{
    if(m_send_messages.empty()) return ;
    //xs_send_group_message_and_clear_container(m_send_messages, *m_socket) ;
    QSocketTratis::send_group_message_and_clear_container(m_send_messages, *m_socket) ;
}




THIS_CLASS::data_type THIS_CLASS::translate_message(int hint, const THIS_CLASS::data_type& db) const
{
    data_type trans ;
    m_translaters.deal_with_message(db.message_type(),
                                    std::make_tuple(hint, std::cref(db), std::ref(trans))) ;
    return trans ;
}

#undef THIS_CLASS
