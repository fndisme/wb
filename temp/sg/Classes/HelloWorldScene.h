#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>

#include "SimpleAudioEngine.h"
namespace WebGame {
  class SparseGraph;
  class TileWindowPosition;
  class SpritePool;
  class TileMask;
  class Player;
  class GameProperty;
}

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    HelloWorld();
    ~HelloWorld();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    void ccTouchEnded(cocos2d::CCTouch* pTouch,
		    cocos2d::CCEvent* pEvent);
    void ccTouchMoved(cocos2d::CCTouch* pTouch,
		    cocos2d::CCEvent* pEvent);
    bool ccTouchBegan(cocos2d::CCTouch* pTouch,
		    cocos2d::CCEvent* pEvent) {
      return true;
    }



private:
    cocos2d::CCTMXTiledMap* m_tileMap;
    cocos2d::CCTMXLayer* m_background;
    cocos2d::CCSprite* m_tileMoveBackgroud;
    cocos2d::CCSprite* m_oldman;
    std::shared_ptr<WebGame::SparseGraph> m_graph;
    std::shared_ptr<WebGame::TileWindowPosition> m_tileWindowPosition;
    std::shared_ptr<WebGame::GameProperty> m_gameProperty;

    cocos2d::CCActionInterval* createRFAnimFormPng(
        cocos2d::CCTexture2D* pTexture,
        const cocos2d::CCSize& frameSize,
        int frames,
        float frameTime);

    void updateAllPosition();
    WebGame::TileMask* m_tileMask;
    WebGame::TileMask* m_attackMask;
    bool m_isMoveScreen;
    void createMask(int x, int y);
    void initImages();
    cocos2d::CCRect m_showMapRect;
    float m_scale;
    cocos2d::CCSize m_tileSize;
    void initTileSystem(const char*);
    void initGameProperty();
    std::map<int,WebGame::Player*> m_players;
    void generateRandomPlayers();
};

#endif  // __HELLOWORLD_SCENE_H__
