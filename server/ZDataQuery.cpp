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
#include "webgame/server/ZDataQueryImpl.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::ZDataQuery

THIS_CLASS::ZDataQuery(QSocketTratis::context_t& ctx,
    boost::asio::strand& strand,
    const std::string& initfile) : m_impl(new Impl(ctx, strand, initfile)) {}

THIS_CLASS::~ZDataQuery() {}

void THIS_CLASS::lock() {
  m_impl->lock() ;
}

void THIS_CLASS::query(const data_type& db) {
  m_impl->query(db) ;
}

void THIS_CLASS::cacheQuery(const THIS_CLASS::cache_data_type cache) {
  m_impl->query(cache) ;
}


void THIS_CLASS::registerTranslater(
    int msgtype,
    THIS_CLASS::message_translater_function const& trans) {
  m_impl->registerTranslater(msgtype, trans) ;
}

THIS_CLASS::data_type THIS_CLASS::translateMessage(int hint,
    const THIS_CLASS::data_type& db) const {
  return m_impl->translateMessage(hint, db) ;
}

void THIS_CLASS::bindPollManager(ZPollInManager* mgr) {
  m_impl->bindPollManager(mgr) ;
}

void THIS_CLASS::registerHandler(
    int msgtype,
    THIS_CLASS::message_handler_function const& func) {
  m_impl->registerHandler(msgtype, func) ;
}

#undef THIS_CLASS
