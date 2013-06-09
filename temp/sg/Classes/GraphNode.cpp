/*
 * =====================================================================================
 *
 *       Filename:  GraphNode.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/9 16:43:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "GraphNode.h"
#include "Player.h"

namespace WebGame {
  GraphNode::pointer GraphNode::create(int index, int x, int y, int type) {
    return pointer(new GraphNode(index, x, y, type));
  }

  void GraphNode::attachPlayer(Player::pointer p) {
    assert(!hasAttachedPlayer());
    m_player = p;
  }

  bool GraphNode::hasAttachedPlayer() const {
    return !m_player.expired();
  }
}
