/*
 * =====================================================================================
 *
 *       Filename:  TestServer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月31日 22时13分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_TEST_SERVER_H
#define FND_TEST_SERVER_H
#include "webgame/server/DefaultZFrontServer.h"

class TestServer : public WebGame::Server::DefaultZFrontServer {
  public:
    TestServer(const OptionType& option);
  private:

  virtual void doDefaultBackMessageCallback(const DataType&) const;
  virtual void doSendMessageToAllConnection(const DataType& db) const ;
  virtual void doOnConnectionLeave(const NetErrorType&, NetConnectionPointer) ;
  virtual bool doIsValidMessage(const DataType& db, NetConnectionPointer nc) const ;
  virtual bool doIsRegisterConnection(NetConnectionPointer nc) const ;
  virtual void doRegisterActions() ;
  virtual void do_deal_back_post_message(const DataType& db, PlayerGroup const&) ;
  virtual void do_deal_back_post_message(const DataType& db, WebGame::player_tt pid) ;
  virtual void do_deal_back_post_message(int, int, int,const DataType& db, PlayerGroup const&) ;
  virtual void do_deal_back_post_message(int, int, int,const DataType& db, WebGame::player_tt pid) ;
  virtual void do_deal_back_post_message(int, int, int,const DataType& db) ;
  virtual void doInitDecoder();

};
#endif
