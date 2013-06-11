#include "HelloWorldScene.h"
#include "SparseGraph.h"
#include "TileWindowPosition.h"
#include "SpritePool.h"
#include "TileMask.h"
#include "GraphBFSFill.h"
#include "GraphNode.h"
#include "GraphProperty.h"

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

        setScale(1.5);

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
//
        initImages();
        m_isMoveScreen = false;

        m_tileMap = CCTMXTiledMap::create("1-1.tmx");
        m_background = m_tileMap->layerNamed("Ground");
        addChild(m_tileMap, -1);
        CCSize mapSize = m_tileMap->getMapSize();
        CCSize tileSize = m_tileMap->getTileSize();
        WebGame::GraphProperty property = WebGame::GraphProperty::buildDefault();
        m_graph = WebGame::SparseGraph::createTileGraph(mapSize.width,
            mapSize.height, property);
        m_tileWindowPosition.reset(new WebGame::TileWindowPosition(
              WebGame::Size(mapSize.width, mapSize.height),
              WebGame::Size(tileSize.width, tileSize.height),
              WebGame::Size(windowSize.width, windowSize.height)));
		this->setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    bRet = true;

    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->textureForKey("move_background.png");
    m_tileMoveBackgroud = CCSprite::createWithTexture(tex);
    addChild(m_tileMoveBackgroud, 4);
    m_tileMoveBackgroud->setPosition(CCPoint(100, 100));

    m_tileMask = 0;
    m_attackMask = 0;

    tex = CCTextureCache::sharedTextureCache()->textureForKey("DQV (1).png");
    m_oldman = CCSprite::createWithTexture(tex, CCRect(0, 0, 48, 48));
    addChild(m_oldman);
//    CCActionInterval* moveInterval = createRFAnimFormPng(tex, CCSize(72, 72), 8,
//        0.08f);
//    CCMoveBy* moveby = CCMoveBy::create(2, ccp(100, 0));
//    CCSpawn* spawn = CCSpawn::create(moveby, moveInterval, 0);
//    sp->runAction(spawn);
    m_oldman->setPosition(ccp(100, 150));
    std::vector<MoveInfo> infos;
    infos.push_back(MoveInfo(MoveInfo::RIGHT, 2));
    infos.push_back(MoveInfo(MoveInfo::UP, 2));
    infos.push_back(MoveInfo(MoveInfo::LEFT, 2));
    infos.push_back(MoveInfo(MoveInfo::DOWN, 2));
    CCActionInterval* action = moveAction("DQV (1).png", infos);
    m_oldman->runAction(CCRepeatForever::create(action));


    } while (0);

    return bRet;
}

void HelloWorld::initImages() {
  CCTextureCache::sharedTextureCache()->addImage("move_background.png");
  CCTextureCache::sharedTextureCache()->addImage("attack_mask.png");
  CCTextureCache::sharedTextureCache()->addImage("aa.png");
  CCTextureCache::sharedTextureCache()->addImage("DQV (1).png");
}

void HelloWorld::createMask(int x, int y) {
  if(m_tileMask) removeChild(m_tileMask);
  if(m_attackMask) removeChild(m_attackMask);

  CCTexture2D* tex =  CCTextureCache::sharedTextureCache()->textureForKey("move_background.png");
  CCTexture2D* texAttack = CCTextureCache::sharedTextureCache()->textureForKey("attack_mask.png");
  assert(tex);
  WebGame::GraphBFSFill<WebGame::SparseGraph> f(*m_graph, m_graph->node(x,y)->index(), 3);
  auto nodes = f.canMoveToNode();
  std::vector<CCPoint> tilePos;
  for(auto v : nodes) {
    auto node = m_graph->node(v);
    tilePos.push_back(ccp(node->x() - x, node->y() - y));
  }
  f.caculateCanInfluenceNodes(WebGame::GraphProperty::SENIOR_ARROWMAN);
  std::vector<CCPoint> infPos;
  const auto& influenceNodes = f.influencedNodes();
  for(auto v : influenceNodes) {
    if(v.second) {
      auto node = m_graph->node(v.first);
      infPos.push_back(ccp(node->x() - x, node->y() - y));
    }
  }
  int mapX = m_tileWindowPosition->x();
  int mapY = m_tileWindowPosition->y();
  m_tileMask = WebGame::TileMask::create(
      tex, // mask
      ccp(48 * x - mapX, 48 * y - mapY),
      ccp(x,y),
      TileSize,
      tilePos);
  addChild(m_tileMask);

  m_attackMask = WebGame::TileMask::create(
      texAttack, // mask
      ccp(48 * x - mapX, 48 * y - mapY),
      ccp(x,y),
      TileSize,
      infPos);
  addChild(m_attackMask);
}

void HelloWorld::updateAllPosition() {
  int x = -m_tileWindowPosition->x();
  int y = -m_tileWindowPosition->y();
  int deltaX = m_tileWindowPosition->deltaX();
  int deltaY = m_tileWindowPosition->deltaY();
  m_tileMap->setPosition(x, y);

  CCPoint pos = m_tileMoveBackgroud->getPosition();
  m_tileMoveBackgroud->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));

  if(m_tileMask) {
    pos = m_tileMask->getPosition();
    m_tileMask->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));
  }
  if(m_attackMask) {
    pos = m_attackMask->getPosition();
    m_attackMask->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));
  }

  pos = m_oldman->getPosition();
  m_oldman->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch* pTouch,
    cocos2d::CCEvent* pEvent) {
  m_isMoveScreen = true;
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
  if(!m_isMoveScreen) {
  CCPoint location = touch->getLocationInView();
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  WebGame::Size size =
    m_tileWindowPosition->getTilePositon(location.x, winSize.height - location.y);
  createMask(size.Width, size.Height);
  } else {
    m_isMoveScreen = false;
  }

//
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
