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
#include "cocos2d.h"
#include <memory>
#include <string>
#include <vector>
class HelloWorld;
namespace WebGame {
  class GraphNode;
  class Player : public cocos2d::CCNode,
  public cocos2d::CCTouchDelegate {
    public:
      const std::string& name() const { return m_name;}
      int id() const { return m_id;}
      Player(int id, const std::string& name) :
        m_id(id),
        m_name(name),
        m_sprite(0){}
      static Player* create(int id, const std::string& name,
          const std::string& texName,
          const cocos2d::CCRect& rect);
      virtual bool init();

      virtual void onEnter();
      virtual void onExit();
      virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
      virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
      virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);


      void bindNode(std::shared_ptr<GraphNode> node);
    private:
      bool hasNode(const std::shared_ptr<GraphNode>& node) const;
      int m_id;
      std::string m_name;
      std::vector<std::shared_ptr<GraphNode> > m_nodes;
      cocos2d::CCSprite* m_sprite;
      HelloWorld* getScene();
  };
}
#endif
