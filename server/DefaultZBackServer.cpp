/*
 * =====================================================================================
 *
 *       Filename:  DefaultZBackServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/21 11:30:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "webgame/server/DefaultZBackServer.h"
#include "webgame/netcore/TimerEvent.h"

#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::Server::DefaultZBackServer

THIS_CLASS::~DefaultZBackServer() NOEXCEPT {}

THIS_CLASS::DefaultZBackServer(const OptionType& option) :
  m_zeroContext(option.ZeroContext),
  m_readStrand(option.ReadStrand),
  m_writeStrand(option.WriteStrand),
  m_decoder(option.Decoder),
  m_propertyFile(option.PropertyFileName) {
  }



#undef THIS_CLASS
