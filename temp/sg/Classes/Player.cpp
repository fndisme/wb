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
#include "Player.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include "HelloWorldScene.h"
#include "GraphNode.h"
#include "TileWindowPosition.h"
#include "utility/MakeAnimation.h"
using namespace cocos2d;

namespace WebGame {

  Player* Player::create(int id, const std::string& name,
      const std::string& texName,
      const CCRect& rect,
      float scale,
      const TileWindowPosition* graph) {
    Player* p = new Player(id, name);
    if(p && p->init()) {
      p->autorelease();
    }
    p->m_animTextureName = texName;
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->textureForKey(texName.c_str());
    p->m_sprite = CCSprite::createWithTexture(tex, rect);
    p->addChild(p->m_sprite);
    p->m_canRevert = true;
    p->m_graph = graph;
    p->m_scale = scale;
    p->setScale(scale);
    return p;
  }

  void Player::onEnter() {
    base_class::onEnter();
    CCDirector::sharedDirector()->
      getTouchDispatcher()->addTargetedDelegate(this, 0, true);
  }

  void Player::onExit() {

    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    base_class::onExit();
  }


  void Player::setPosition(const CCPoint& pos) {
    CCNode::setPosition(pos);
    m_mapPosition = m_graph->getTilePosition(pos.x, pos.y);
  }

  void Player::moveTo(const CCPoint& pos, const std::vector<CCPoint>& path) {
    if(!path.empty()) {
      std::vector<MoveInfo> moveInfos;
      for(auto& p : path) {
        moveInfos.push_back(MoveInfo(p));
      }

      auto action = createAnimation(m_animTextureName,
          moveInfos,
          CCSize(48, 48),
          4,
          0.1f,
          1);
      //CCHide * hide= CCHide::create();
      m_sprite->runAction(action);
      action = createMoveAction(
          moveInfos,
          CCSize(48 * m_scale, 48 * m_scale),
          0.4f);
      CCCallFunc* fun = CCCallFunc::create(getScene(), callfunc_selector(HelloWorld::inChooseActionState));

      runAction(CCSequence::create(action, fun, 0));
    }

  }

  void Player::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    m_isMoveScreen = true;
    if(auto scene = getScene()) {
      scene->ccTouchMoved(touch, event);
    }
  }

  void Player::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    if(!m_isMoveScreen)
      getScene()->showMaskInMap(touch->getLocationInView(), this);
    m_isMoveScreen = false;
  }

  bool Player::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint point =
      this->convertTouchToNodeSpace(touch);
    const CCSize& size = getContentSize();
    CCRect box = m_sprite->boundingBox();
    int containtit = box.containsPoint(point);
    return box.containsPoint(point);
  }

  bool Player::init() {
    if(!base_class::init()) return false;
    return true;
  }

  HelloWorld* Player::getScene() {
    auto parent = getParent();
    if(parent) return dynamic_cast<HelloWorld*>(parent);
    return 0;
  }

  bool Player::hasNode(const GraphNode::pointer& node) const {
    return std::find_if(m_nodes.cbegin(), m_nodes.cend(),
        [&node](GraphNode::const_pointer v) -> bool {
          return node->index() == v->index() ;
        }) != m_nodes.cend();
  }

  void Player::bindNode(GraphNode::pointer node) {
    assert(!hasNode(node));
    m_nodes.push_back(node);
    node->attachPlayer(this);
  }
}
