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
#include <memory>
#include "webgame/server/DefaultZFrontServer.h"
#include "webgame/server/ClientSet.h"
#include "webgame/server/FrontClientStub.h"

class TestServer : public WebGame::Server::DefaultZFrontServer {
  public:
    TestServer(const OptionType& option);
  private:
    typedef WebGame::Server::FrontClientStub FrontClientStub;
    virtual void doMakeConnectionValid(NetConnectionPointer nc);
    virtual void doDefaultBackMessageCallback(const DataType&) const;
    virtual void doSendMessageToAllConnection(const DataType& db) const ;
    virtual void doOnConnectionLeave(const NetErrorType&, NetConnectionPointer) ;
    virtual bool doIsValidMessage(const DataType& db, NetConnectionPointer nc) const ;
    virtual bool doIsRegisterConnection(NetConnectionPointer nc) const ;
    virtual void doRegisterActions() ;
    virtual void doDealBackServerPostMessage(const DataType& db,
                                             PlayerGroup const& group);
    virtual void doDealBackServerGroupMessage(const MiniGroup&,
                                              const DataType& db,
                                              PlayerGroup const& clientsIds);

  // handlers
  void handleLogin(MessageHandlerType param);
  typedef boost::multi_index::multi_index_container<
    std::shared_ptr<FrontClientStub>,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique<WebGame::Server::sortByConnection<FrontClientStub>>,
    boost::multi_index::ordered_non_unique<WebGame::Server::sortById<FrontClientStub>>,
    boost::multi_index::ordered_non_unique<WebGame::Server::sortBySession<FrontClientStub>>
      > > ClientSet;

  ClientSet m_justConnected;
  ClientSet m_justLoggining;
  ClientSet m_justLoggined;
  int64_t m_startSessionId;
  void removePlayerFromSet(ClientSet& clients, NetConnectionPointer nc) {
    clients.get<0>().erase(nc);
  }

  enum class LoginType {
    Normal,
    Forced
  };
  FrontClientStub::pointer makeClientLoginning(NetConnectionPointer nc);
  FrontClientStub::pointer makeClientLoginned(int64_t sessionId,
                                              FrontClientStub::IdType pid,
                                              LoginType type);
  FrontClientStub::pointer justConnectedPlayer(NetConnectionPointer nc);
  FrontClientStub::pointer justLoginningPlayer(int64_t sessionId);
  void removeJustConnectPlayer(NetConnectionPointer nc);
  bool removeJustLoginningPlayer(FrontClientStub::pointer p);
  bool hasLoginnedPlayer(FrontClientStub::IdType pid) const;
  bool hasLoginnedPlayer(int64_t sessionId) const;
  void removePlayerFromPlayerSet(NetConnectionPointer nc);

};
#endif
