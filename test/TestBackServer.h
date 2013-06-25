/*
 * =====================================================================================
 *
 *       Filename:  TestBackServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/24 16:24:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_TEST_BACKSERVER_H
#define FND_TEST_BACKSERVER_H
#include <string>
#include <map>
#include <set>
#include "webgame/server/DefaultZBackServer.h"
class TestBackServer : public WebGame::Server::DefaultZBackServer {
  public:
    typedef WebGame::Server::DefaultZBackServer base_class;
    TestBackServer(OptionType const& option) : base_class(option),m_startSessionId(0) {}
  private:
    virtual void doInitCallback();
    void handleInnerLogin(const MessageDealerType::ParamType& param);
    std::map<std::string, WebGame::player_tt> m_players;
    std::map<WebGame::player_tt, std::string> m_names;
    bool hasPlayer(const std::string& name) const {
      return m_players.count(name) > 0;
    }
    bool hasPlayer(WebGame::player_tt pid) const {
      return m_names.count(pid) > 0;
    }
    int64_t m_startSessionId;
};
#endif
