#include "HelloWorldScene.h"
#include "SparseGraph.h"
#include "TileWindowPosition.h"
#include "SpritePool.h"
#include "TileMask.h"
#include "GraphBFSFill.h"
#include "GraphNode.h"
#include "GraphProperty.h"
#include "GUI/ShowDialog.h"
#include "utility/MakeAnimation.h"
#include "Player.h"
#include "GameProperty.h"

using namespace cocos2d;
static const float MoveSpeed(0.8f);

HelloWorld::HelloWorld() :
  m_tileMap(0),
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
//
        initGameProperty();
        initImages();

//        WebGame::GUI::ShowDialog* showDialog =
//          WebGame::GUI::ShowDialog::create("aa.json");
//        showDialog->setPosition(200, 200);
//        addChild(showDialog);
//
        initTileSystem("1-1.tmx");
        CCSize mapSize = m_tileMap->getMapSize();
        CCSize tileSize = m_tileMap->getTileSize();
        CCSize showSize(mapSize.width * m_tileSizeWithScale.width,
            mapSize.height * m_tileSizeWithScale.height);
        if(showSize.width > windowSize.width) showSize.width = windowSize.width;
        if(showSize.height > windowSize.height) showSize.height = windowSize.height;
        // window size >= show size
        // all the move must in the m_showMapRect

        //m_tileMap->setContentSize(showSize);

        //m_tileMap->setTextureRect(CCRect(0, 0, 100, 100));
        m_showMapRect.setRect((windowSize.width - showSize.width)/2,
            (windowSize.height - showSize.height)/2,
            showSize.width, showSize.height);
        m_tileWindowPosition.reset(new WebGame::TileWindowPosition(
              mapSize,
              m_tileSizeWithScale,
              showSize,
              windowSize,
              ccp(0.5f, 0.5f))); // point in window (0 -- 1)
		this->setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    generateRandomPlayers();

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
    m_oldman->setPosition(ccp(100, 150));
    using WebGame::MoveInfo;
    std::vector<MoveInfo> infos;
    infos.push_back(MoveInfo(MoveInfo::RIGHT, 2));
    infos.push_back(MoveInfo(MoveInfo::UP, 2));
    infos.push_back(MoveInfo(MoveInfo::LEFT, 2));
    infos.push_back(MoveInfo(MoveInfo::DOWN, 2));
    CCActionInterval* action = WebGame::createMoveAnimationAction("DQV (1).png", infos,
        m_tileSizeWithScale,
        4,
        0.04f,
        2,
        MoveSpeed
        );
    m_oldman->runAction(CCRepeatForever::create(action));

    } while (0);

    return bRet;
}

void HelloWorld::initGameProperty() {
  m_isMoveScreen = false;
  m_currentState = S_IDLE;
  m_gameProperty = std::make_shared<WebGame::GameProperty>();
  m_gameProperty->initPlayerMetaFromFile("playerMetas.json");
  CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
  m_scale =  windowSize.width / 960.0f;
}

void HelloWorld::generateRandomPlayers() {
  CCSize tileSize = m_tileMap->getTileSize();
  CCPoint pos1(4 * tileSize.width, 4 * tileSize.height);
  CCPoint pos2(5 * tileSize.width, 8 * tileSize.height);

  using WebGame::Player;
  CCRect rect(0,0,48,48);
  Player* p = Player::create(0, "aa", "DQV (1).png", rect, m_tileWindowPosition.get());
  p->setMeta(*(m_gameProperty->playerMeta(1)));
  addChild(p, 10);
  p->setPosition(pos1);
  m_players[p->id()] = p;
  p = Player::create(1, "bb","DQV (1).png", rect, m_tileWindowPosition.get());
  addChild(p, 10);
  p->setPosition(pos2);
  p->setMeta(*(m_gameProperty->playerMeta(2)));
  m_players[p->id()] = p;
}

void HelloWorld::createMap(const char* mapName) {
  m_tileMap = CCTMXTiledMap::create(mapName);
  assert(m_tileMap);
  m_tileMap->setAnchorPoint(ccp(0.5f, 0.5f));
  m_tileMap->setScale(m_scale);
  CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
  m_tileMap->setPosition(ccp(windowSize.width/2, windowSize.height/2));
  m_tileSizeWithScale =
    CCSize(m_tileMap->getTileSize().width * m_scale,
        m_tileMap->getTileSize().height * m_scale);
  addChild(m_tileMap, -1);
  m_background = m_tileMap->layerNamed("Ground");

//  CCObject* pObj = NULL;
//  CCARRAY_FOREACH(m_tileMap->getChildren(), pObj)
//  {
//    CCSpriteBatchNode* child = (CCSpriteBatchNode*)pObj;
//    child->getTexture()->setAntiAliasTexParameters();
//  }
//
}

void HelloWorld::initTileSystem(const char* tileMapName) {
  createMap(tileMapName);
  createLogicGraph(m_tileMap->getTileSize());
}

void HelloWorld::createLogicGraph(const CCSize& mapSize) {
  WebGame::GraphProperty property = WebGame::GraphProperty::buildDefault();
  m_graph = WebGame::SparseGraph::createTileGraph(mapSize.width,
      mapSize.height, property);
}

void HelloWorld::initImages() {
  CCTextureCache::sharedTextureCache()->addImage("move_background.png");
  CCTextureCache::sharedTextureCache()->addImage("attack_mask.png");
  CCTextureCache::sharedTextureCache()->addImage("aa.png");
  CCTextureCache::sharedTextureCache()->addImage("DQV (1).png");
}

void HelloWorld::createMask(int x, int y, WebGame::Player* p) {
  if(m_tileMask) removeChild(m_tileMask);
  if(m_attackMask) removeChild(m_attackMask);

  CCTexture2D* tex =  CCTextureCache::sharedTextureCache()->textureForKey("move_background.png");
  CCTexture2D* texAttack = CCTextureCache::sharedTextureCache()->textureForKey("attack_mask.png");
  assert(tex);
  m_searcher.reset(new WebGame::GraphBFSFill<WebGame::SparseGraph>
      (*m_graph, m_graph->node(x,y)->index(), p->meta().MoveStep));
  CCLog("create mask %d %d", x, y);
  auto nodes = m_searcher->canMoveToNode();
  std::vector<CCPoint> tilePos;
  for(auto v : nodes) {
    auto node = m_graph->node(v);
    tilePos.push_back(ccp(node->x() - x, node->y() - y));
  }
  m_searcher->caculateCanInfluenceNodes(WebGame::GraphProperty::SENIOR_ARROWMAN);
  std::vector<CCPoint> infPos;
  const auto& influenceNodes = m_searcher->influencedNodes();
  for(auto v : influenceNodes) {
    if(v.second) {
      auto node = m_graph->node(v.first);
      infPos.push_back(ccp(node->x() - x, node->y() - y));
    }
  }
  int mapX = m_tileWindowPosition->x();
  int mapY = m_tileWindowPosition->y();
  int minX = m_showMapRect.getMinX();
  int minY = m_showMapRect.getMinY();
  m_tileMask = WebGame::TileMask::create(
      tex, // mask
      ccp(m_tileSizeWithScale.width * x - m_tileWindowPosition->realDeltaX(),
        m_tileSizeWithScale.height * y - m_tileWindowPosition->realDeltaY()),
      ccp(x,y),
      m_tileSizeWithScale,
      m_scale,
      std::move(tilePos));
  addChild(m_tileMask);

  m_attackMask = WebGame::TileMask::create(
      texAttack, // mask
      ccp(m_tileSizeWithScale.width * x - m_tileWindowPosition->realDeltaX(),
        m_tileSizeWithScale.height * y - m_tileWindowPosition->realDeltaY()),
      ccp(x,y),
      m_tileSizeWithScale,
      m_scale,
      std::move(infPos));
  addChild(m_attackMask);
}

void HelloWorld::updateAllPosition() {
  int x = -m_tileWindowPosition->x();
  int y = -m_tileWindowPosition->y();
  int deltaX = m_tileWindowPosition->deltaX();
  int deltaY = m_tileWindowPosition->deltaY();
  m_tileMap->setPosition(x + m_tileWindowPosition->initX(), y + m_tileWindowPosition->initY());

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

  for(auto& v : m_players) {
    const auto& pos = v.second->getPosition();
    v.second->setPosition(ccp(pos.x - deltaX, pos.y - deltaY));
  }
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch* pTouch,
    cocos2d::CCEvent* pEvent) {
  m_isMoveScreen = true;
  CCPoint delta = pTouch->getDelta();
  m_tileWindowPosition->moveDelta(-delta.x, -delta.y);
  updateAllPosition();
  const CCPoint& pos = m_tileMap->getPosition();
  m_tileMap->setPosition(-m_tileWindowPosition->x() +
      m_tileWindowPosition->initX(), -m_tileWindowPosition->y() +
      m_tileWindowPosition->initY());
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

bool HelloWorld::inCanChooseState() const {
  if(m_currentState == S_IDLE || m_currentState == S_CHOOSE) return true;
  return false;
}

void HelloWorld::showMaskInMap(const CCPoint& viewPoint, WebGame::Player* p) {
  if(!inCanChooseState()) return;
  m_currentState = S_CHOOSE;
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  // FIXME has bug in next line
  //if(m_showMapRect.containsPoint(viewPoint)) {
  m_currentPlayer = p;
  CCPoint pos = m_tileWindowPosition->
    getTilePositon(viewPoint.x, winSize.height - viewPoint.y);
  createMask(pos.x, pos.y, p);
 // }
}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch* touch,
		    cocos2d::CCEvent* pEvent) {
  if(!m_isMoveScreen) {
    auto pos = touch->getLocationInView();
    if(checkInMoveMask(pos)) {
      inPlayerMoveState(viewPointToMapPos(pos));
    }
  } else {
    m_isMoveScreen = false;
  }
}

cocos2d::CCPoint HelloWorld::viewPointToMapPos(const cocos2d::CCPoint& pointInView) {

  const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
  return m_tileWindowPosition->
    getTilePositon(pointInView.x, winSize.height - pointInView.y);
}

void HelloWorld::inPlayerMoveState(const cocos2d::CCPoint& position) {
  assert(m_graph->hasNode(position.x, position.y));
  auto node = m_graph->node(position.x, position.y);
  auto path = m_searcher->pathToTarget(node->index());
  std::vector<CCPoint> deltaPositions;
  const auto& originPos = m_currentPlayer->tilePosition();
  for(const auto& index : path) {
    auto n = m_graph->node(index);
    deltaPositions.push_back(ccp(n->x() - originPos.x, n->y() - originPos.y));
  }

  m_currentPlayer->moveTo(position, deltaPositions);
  m_currentState = S_PLAYER_MOVE;
}

bool HelloWorld::checkInMoveMask(const cocos2d::CCPoint& pointInView) {

  if(m_showMapRect.containsPoint(pointInView)) {
    if(m_currentPlayer && m_tileMask) {
      auto pos = viewPointToMapPos(pointInView);
      return m_tileMask->hasPosition(pos);
    }
  }
  return false;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
