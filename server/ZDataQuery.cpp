/*
 * =====================================================================================
 *
 *       Filename:  ZDataQuery.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-18 15:05:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#include "ZDataQueryImpl.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::ZDataQuery

THIS_CLASS::ZDataQuery(QSocketTratis::context_t& ctx,
                       const std::string& initfile) : m_impl(new Impl(ctx, initfile)) {}

THIS_CLASS::~ZDataQuery() {}

void THIS_CLASS::lock()
{
    m_impl->lock() ;
}

void THIS_CLASS::query(const Fnd::data_block& db)
{
    m_impl->query(db) ;
}

void THIS_CLASS::cache_query(const THIS_CLASS::cache_data_type cache)
{
    m_impl->query(cache) ;
}


void THIS_CLASS::register_tranlater(
    int msgtype,
    THIS_CLASS::message_translater_function const& trans)
{
    m_impl->register_tranlater(msgtype, trans) ;
}

THIS_CLASS::data_type THIS_CLASS::translate_message(int hint,
        const THIS_CLASS::data_type& db) const
{
    return m_impl->translate_message(hint, db) ;
}

void THIS_CLASS::bind_to_poll_manager(WebGame::ZPollInManager* mgr)
{
    m_impl->bind_to_poll_manager(mgr) ;
}

void THIS_CLASS::register_handler(
    int msgtype,
    THIS_CLASS::message_handler_function const& func)
{
    m_impl->register_handler(msgtype, func) ;
}

#undef THIS_CLASS
