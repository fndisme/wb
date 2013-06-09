/*
 * =====================================================================================
 *
 *       Filename:  Player.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/9 16:16:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_PLAYER_H
#define FND_WEBGAME_PLAYER_H

#include <memory>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
namespace WebGame {
  class GraphNode;
  class Player : public std::enable_shared_from_this<Player>,
  boost::noncopyable {
    public:
      typedef std::shared_ptr<Player> pointer;
      typedef std::shared_ptr<const Player> const_pointer;
      const std::string& name() const { return m_name;}
      int id() const { return m_id;}
      Player(int id, const std::string& name) :
        m_id(id),
        m_name(name) {}

      void bindNode(std::shared_ptr<GraphNode> node);
    private:
      bool hasNode(const std::shared_ptr<GraphNode>& node) const;
      int m_id;
      std::string m_name;
      std::vector<std::shared_ptr<GraphNode> > m_nodes;
  };
}
#endif
