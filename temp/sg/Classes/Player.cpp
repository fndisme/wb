/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/9 16:25:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <cassert>
#include <algorithm>
#include <functional>
#include "Player.h"
#include "GraphNode.h"

namespace WebGame {
  bool Player::hasNode(const GraphNode::pointer& node) const {
    return std::find_if(m_nodes.cbegin(), m_nodes.cend(),
        [&node](GraphNode::const_pointer v) -> bool {
          return node->index() == v->index() ;
        }) != m_nodes.cend();
  }

  void Player::bindNode(GraphNode::pointer node) {
    assert(!hasNode(node));
    m_nodes.push_back(node);
    node->attachPlayer(this->shared_from_this());
  }
}
