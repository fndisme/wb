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
//
        initGameProperty();
        initImages();


//        CCScale9Sprite* tes = CCScale9Sprite::create("attack_mask.png", CCRect(0, 0, 200, 200), CCRect(10, 10, 10, 10));
//        tes->setPosition(ccp(150, 150));
//        addChild(tes);
        //WebGame::GUI::ShowDialog* showDialog =
        //  WebGame::GUI::ShowDialog::create("这是一个历史悠久的故事", "attack_mask.png",
         //     "move_background.png", 0);

        WebGame::GUI::ShowDialog* showDialog =
          WebGame::GUI::ShowDialog::create("aa.json");
        showDialog->setPosition(200, 200);
        addChild(showDialog);

        m_isMoveScreen = false;

        initTileSystem("1-1.tmx");

        CCSize mapSize = m_tileMap->getMapSize();
        CCSize tileSize = m_tileMap->getTileSize();
        m_tileSize = CCSize(tileSize.width * m_tileMap->getScale(), tileSize.height * m_tileMap->getScale());
        WebGame::GraphProperty property = WebGame::GraphProperty::buildDefault();
        m_graph = WebGame::SparseGraph::createTileGraph(mapSize.width,
            mapSize.height, property);
        CCSize showSize(mapSize.width * m_tileSize.width, mapSize.height * m_tileSize.height);
        if(showSize.width > windowSize.width) showSize.width = windowSize.width;
        if(showSize.height > windowSize.height) showSize.height = windowSize.height;
        m_showMapRect.setRect((windowSize.width - showSize.width)/2, (windowSize.height - showSize.height)/2,
            showSize.width, showSize.height);
        m_tileWindowPosition.reset(new WebGame::TileWindowPosition(
              mapSize,
              m_tileSize,
              showSize,
              windowSize,
              ccp(windowSize.width/2, windowSize.height/2)));
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
        m_tileSize,
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
  m_gameProperty = std::make_shared<WebGame::GameProperty>();
  m_gameProperty->initPlayerMetaFromFile("playerMetas.json");
}

void HelloWorld::generateRandomPlayers() {
  CCSize tileSize = m_tileMap->getTileSize();
  CCPoint pos1(4 * tileSize.width, 4 * tileSize.height);
  CCPoint pos2(5 * tileSize.width, 8 * tileSize.height);

  using WebGame::Player;
  CCRect rect(0,0,48,48);
  Player* p = Player::create(0, "aa", "DQV (1).png", rect);
  addChild(p);
  p->setPosition(pos1);
  m_players[p->id()] = p;
  p = Player::create(1, "bb","DQV (1).png", rect);
  addChild(p);
  p->setPosition(pos2);
  m_players[p->id()] = p;
}

void HelloWorld::initTileSystem(const char* tileMapName) {
  CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
  m_tileMap = CCTMXTiledMap::create(tileMapName);
  assert(m_tileMap);
  m_tileMap->setAnchorPoint(ccp(0.5f, 0.5f));
  m_scale =  windowSize.width / 640.0f;
  m_tileMap->setScale(m_scale);
  m_tileMap->setPosition(ccp(windowSize.width/2, windowSize.height/2));
  m_background = m_tileMap->layerNamed("Ground");
  addChild(m_tileMap, -1);
  CCSize tileSize = m_tileMap->getTileSize();
  m_tileSize = CCSize(tileSize.width * m_tileMap->getScale(), tileSize.height * m_tileMap->getScale());
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
  WebGame::GraphBFSFill<WebGame::SparseGraph> f(*m_graph, m_graph->node(x,y)->index(), 0);
  CCLog("create mask %d %d", x, y);
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
  int minX = m_showMapRect.getMinX();
  int minY = m_showMapRect.getMinY();
  m_tileMask = WebGame::TileMask::create(
      tex, // mask
      ccp(m_tileSize.width * x - m_tileWindowPosition->realDeltaX(), m_tileSize.height * y - m_tileWindowPosition->realDeltaY()),
      ccp(x,y),
      m_tileSize,
      m_scale,
      tilePos);
  addChild(m_tileMask);

  m_attackMask = WebGame::TileMask::create(
      texAttack, // mask
      ccp(m_tileSize.width * x - m_tileWindowPosition->realDeltaX(), m_tileSize.height * y - m_tileWindowPosition->realDeltaY()),
      ccp(x,y),
      m_tileSize,
      m_scale,
      infPos);
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
    v.second->setPosition(pos.x - deltaX, pos.y - deltaY);
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

void HelloWorld::ccTouchEnded(cocos2d::CCTouch* touch,
		    cocos2d::CCEvent* pEvent) {
  if(!m_isMoveScreen) {
    CCPoint location = touch->getLocationInView();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(m_showMapRect.containsPoint(location)) {
      CCPoint pos =
        m_tileWindowPosition->getTilePositon(location.x, winSize.height - location.y);
      createMask(pos.x, pos.y);
    }
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
