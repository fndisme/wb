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
#include "webgame/netcore/DefaultNetConnectionDef.h"
#include "webgame/shared/identity_type.h"
namespace WebGame {
namespace Server {
class FrontClientStub : boost::noncopyable {
  typedef FrontClientStub class_type;
  public:
    typedef std::shared_ptr< ::WebGame::NetCore::DefaultNetConnectType> ConnectionType;
    typedef WebGame::player_tt IdType;
    typedef std::shared_ptr<FrontClientStub> pointer;
    ConnectionType connection() { return m_connection;}
    IdType id() const { return m_id;}
    explicit FrontClientStub(ConnectionType conn, IdType id = IdType(0)) :
      m_connection(conn),
      m_id(id) {}
    FrontClientStub() : m_connection(), m_id(0) {}
    virtual ~FrontClientStub() {}
    void setId(IdType newId) { m_id = newId;}
    static pointer create(ConnectionType conn, IdType id = IdType(0)) {
      auto p = std::make_shared<class_type>();
      p->m_connection = conn;
      p->setId(id);
      return p;
    }
  private:
    ConnectionType m_connection;
    IdType m_id;
};
}
}

#endif
