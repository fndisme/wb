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
#include "PlayerMeta.h"
#include "Weapon.h"

class HelloWorld;
namespace WebGame {
  class Weapon;
  class GraphNode;
  class BagObject;
  class TileWindowPosition;
  class Player : public cocos2d::CCNode,
  public cocos2d::CCTouchDelegate {
    typedef cocos2d::CCNode base_class;
    public:
      const std::string& name() const { return m_name;}
      int id() const { return m_id;}
      Player(int id, const std::string& name) :
        m_id(id),
        m_name(name),
        m_sprite(0),
        m_isMoveScreen(false),
        m_graph(0),
        m_scale(1.0f),
        m_color(0){}
      static Player* create(int id, const std::string& name,
          const std::string& texName,
          const cocos2d::CCRect& rect,
          float scale,
          const TileWindowPosition*);
      virtual bool init();

      virtual void onEnter();
      virtual void onExit();
      virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
      virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
      virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);


      void bindNode(std::shared_ptr<GraphNode> node);
      void setMeta(const PlayerMeta& meta) { m_meta = meta; m_oldMeta = meta;}
      const PlayerMeta& meta() const { return m_meta;}
      void revertMeta() {
        if(m_canRevert) {
          m_meta = m_oldMeta;
          m_canRevert = false;
        }
      }
      const Weapon* currentWeapon() const {
        return m_currentWeapon;
      }
      bool isBagFull() const;
      void pushBagObject(BagObject* object);
      void exchangeBag(int lhs, int rhs);
      void moveTo(const cocos2d::CCPoint& pos,
          const std::vector<cocos2d::CCPoint>& path);
      virtual void setPosition(const cocos2d::CCPoint& pos);
      const cocos2d::CCPoint& tilePosition() const { return m_mapPosition;}
      int color() const { return m_color;}
      void setColor(int c) { m_color = c;}
    private:
      bool hasNode(const std::shared_ptr<GraphNode>& node) const;
      int m_id;
      std::string m_name;
      std::string m_animTextureName;
      std::vector<std::shared_ptr<GraphNode> > m_nodes;
      cocos2d::CCSprite* m_sprite;
      HelloWorld* getScene();
      PlayerMeta m_meta;
      PlayerMeta m_oldMeta;
      bool m_canRevert;
      Weapon* m_currentWeapon;
      bool m_isMoveScreen;
      const TileWindowPosition* m_graph;
      cocos2d::CCPoint m_mapPosition;
      float m_scale;
      int m_color;
  };
}
#endif
