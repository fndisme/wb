#include "HelloWorldScene.h"
#include "SparseGraph.h"
#include "TileWindowPosition.h"
#include "SpritePool.h"
#include "TileMask.h"

using namespace cocos2d;

static const CCSize TileSize(48, 48);
static const float MoveSpeed(0.8f);

HelloWorld::HelloWorld() : m_tileMap(0),
  m_background(0),
  m_tileMoveBackgroud(0){}

HelloWorld::~HelloWorld() {}

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper.
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

//        // 3. Add add a splash screen, show the cocos2d splash image.
//        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//        CC_BREAK_IF(! pSprite);
//
//        // Place the sprite on the center of the screen
//        pSprite->setPosition(ccp(size.width/2, size.height/2));
//
//        // Add the sprite to HelloWorld layer as a child layer.
//        this->addChild(pSprite, 0);
//

        m_tileMap = CCTMXTiledMap::create("1-1.tmx");
        m_background = m_tileMap->layerNamed("Ground");
        addChild(m_tileMap, -1);
        CCSize mapSize = m_tileMap->getMapSize();
        CCSize tileSize = m_tileMap->getTileSize();
        m_graph = WebGame::SparseGraph::createTileGraph(mapSize.width,
            mapSize.height);
        m_tileWindowPosition.reset(new WebGame::TileWindowPosition(
              WebGame::Size(mapSize.width, mapSize.height),
              WebGame::Size(tileSize.width, tileSize.height),
              WebGame::Size(windowSize.width, windowSize.height)));
		this->setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    bRet = true;

    CCTexture2D* tex =  CCTextureCache::sharedTextureCache()->addImage("move_background.png");
    m_tileMoveBackgroud = CCSprite::createWithTexture(tex);
    addChild(m_tileMoveBackgroud, 4);
    m_tileMoveBackgroud->setPosition(CCPoint(100, 100));

    std::vector<CCPoint> tilePos;
    tilePos.push_back(ccp(0, 0));
    tilePos.push_back(ccp(0, 1));
    tilePos.push_back(ccp(1, 0));
    m_tileMask = WebGame::TileMask::create(tex, ccp(48 * 2, 48 * 2), CCPointZero, TileSize, tilePos);
    addChild(m_tileMask);

    tex =  CCTextureCache::sharedTextureCache()->addImage("aa.png");
    tex = CCTextureCache::sharedTextureCache()->addImage("DQV (1).png");
    CCSprite* sp = CCSprite::createWithTexture(tex, CCRect(0, 0, 48, 48));
    addChild(sp);
//    CCActionInterval* moveInterval = createRFAnimFormPng(tex, CCSize(72, 72), 8,
//        0.08f);
//    CCMoveBy* moveby = CCMoveBy::create(2, ccp(100, 0));
//    CCSpawn* spawn = CCSpawn::create(moveby, moveInterval, 0);
//    sp->runAction(spawn);
    sp->setPosition(ccp(100, 150));
    std::vector<MoveInfo> infos;
    infos.push_back(MoveInfo(MoveInfo::RIGHT, 2));
    infos.push_back(MoveInfo(MoveInfo::UP, 2));
    infos.push_back(MoveInfo(MoveInfo::LEFT, 2));
    infos.push_back(MoveInfo(MoveInfo::DOWN, 2));
    CCActionInterval* action = moveAction("DQV (1).png", infos);
    sp->runAction(action);


    } while (0);

    return bRet;
}

void HelloWorld::updateAllPosition() {
  int x = -m_tileWindowPosition->x();
  int y = -m_tileWindowPosition->y();
  int deltaX = m_tileWindowPosition->deltaX();
  int deltaY = m_tileWindowPosition->deltaY();
  m_tileMap->setPosition(x, y);

  CCPoint pos = m_tileMoveBackgroud->getPosition();
  m_tileMoveBackgroud->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));

  pos = m_tileMask->getPosition();
  m_tileMask->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch* pTouch,
    cocos2d::CCEvent* pEvent) {
  CCPoint delta = pTouch->getDelta();
  m_tileWindowPosition->moveDelta(-delta.x, -delta.y);
  updateAllPosition();
  m_tileMap->setPosition(-m_tileWindowPosition->x(), -m_tileWindowPosition->y());

}


CCActionInterval* HelloWorld::createRFAnimFormPng(
    CCTexture2D* playerRunTexture,
    const CCSize& frameSize,int frames,
    float frameTime) {
    CCAnimation* animation = CCAnimation::create();
    for( int i = 0;i < frames;i++){
      CCRect rect(frameSize.width * i, 0, frameSize.width, frameSize.height);
        animation->addSpriteFrame(CCSpriteFrame::createWithTexture(playerRunTexture,
              rect));
    }
    animation->setDelayPerUnit(frameTime);
    CCAnimate* action = CCAnimate::create(animation);
    return CCRepeat::create(action, 2);
}

cocos2d::CCActionInterval* HelloWorld::createRFAnimFormTexture(
        cocos2d::CCTexture2D* pTexture,
        const MoveInfo& moveInfo,
        const cocos2d::CCSize& frameSize,
        int frames,
        float frameTime) {
  CCAnimation* animation = CCAnimation::create();
  for( int i = 0;i < frames;i++){
    CCRect rect(frameSize.width * i,
        moveInfo.Direction * frameSize.height,
        frameSize.width,
        frameSize.height);
    animation->addSpriteFrame(CCSpriteFrame::createWithTexture(pTexture,
          rect));
  }
  animation->setDelayPerUnit(frameTime);
  CCAnimate* action = CCAnimate::create(animation);
  return CCRepeat::create(action, moveInfo.Step * 2);
}

cocos2d::CCActionInterval* HelloWorld::moveAction(
        const char* baseName,
        const std::vector<MoveInfo>& moveInfo) {

  CCTexture2D* tex =  CCTextureCache::sharedTextureCache()->textureForKey(baseName);
  CCArray* arr = CCArray::create();
  for(int i = 0 ; i < moveInfo.size() ; ++i) {
    CCActionInterval* act = createRFAnimFormTexture(
        tex, moveInfo[i],
        TileSize,
        4,
        0.04f);
    assert(act);
    CCActionInterval* moveStep = createMoveStep(
        moveInfo[i]);
    assert(moveStep);
    CCSpawn* spawn = CCSpawn::create(act, moveStep, 0);
    arr->addObject(spawn);
  }
  CCSequence* seq = CCSequence::create(arr);
  return seq;
}
cocos2d::CCActionInterval* HelloWorld::createMoveStep(
    const MoveInfo& info) {
  CCPoint moved(0, 0);
  switch (info.Direction) {
    case MoveInfo::LEFT :
      {
        moved.x = -TileSize.width * info.Step;
        break;
      }
    case MoveInfo::RIGHT :
      {
        moved.x = TileSize.width * info.Step;
        break;
      }
    case MoveInfo::UP:
      {
        moved.y = TileSize.height * info.Step;
        break;
      }
    case MoveInfo::DOWN:
      {
        moved.y = -TileSize.height * info.Step;
        break;
      }
    default:
      assert(false);
      break;
  }
  CCMoveBy* moveBy = CCMoveBy::create(MoveSpeed, moved);
  return moveBy;
}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch* touch,
		    cocos2d::CCEvent* pEvent) {
//  CCPoint location = touch->getLocationInView();
//  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//  m_tileWindowPosition->update(location.x, winSize.height - location.y);
//  m_tileMap->setPosition(-m_tileWindowPosition->x(), -m_tileWindowPosition->y());
//
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
