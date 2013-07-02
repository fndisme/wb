/*
 * =====================================================================================
 *
 *       Filename:  FrontClientStub.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/25 9:40:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVER_FRONTCLIENTSTUB_H
#define FND_WEBGAME_SERVER_FRONTCLIENTSTUB_H
#include <memory>
#include <boost/noncopyable.hpp>
#include "webgame/message/DataBlock.h"
#include "webgame/netcore/DefaultNetConnectionDef.h"
#include "webgame/netcore/Connection.h"
#include "webgame/shared/identity_type.h"
namespace WebGame {
namespace Server {
class FrontClientStub : boost::noncopyable {
  typedef FrontClientStub class_type;
  public:
    typedef std::shared_ptr< ::WebGame::NetCore::DefaultNetConnectType> ConnectionType;
    typedef WebGame::player_tt IdType;
    typedef int64_t SessionType;
    typedef std::shared_ptr<FrontClientStub> pointer;
    ConnectionType connection() { return m_connection;}
    IdType id() const { return m_id;}
    SessionType session() const { return m_session;}
    void setSession(int64_t session) { m_session = session;}
    explicit FrontClientStub(ConnectionType conn, IdType id = IdType(0)) :
      m_connection(conn),
      m_id(id),
      m_session(0){}
    FrontClientStub() : m_connection(), m_id(0), m_session(0) {}
    virtual ~FrontClientStub() {}
    void setId(IdType newId) { m_id = newId;}
    static pointer create(ConnectionType conn, IdType id = IdType(0)) {
      auto p = std::make_shared<class_type>();
      p->m_connection = conn;
      p->setId(id);
      return p;
    }
    template<typename MSG>
    void sendAsyncMessage(MSG&& msg) {
      if(m_connection)
        m_connection->sendAsyncMessage(std::forward<MSG>(msg));
    }
  private:
    ConnectionType m_connection;
    IdType m_id;
    SessionType m_session;
};
}
}

#endif
