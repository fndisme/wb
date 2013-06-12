/*
 * =====================================================================================
 *
 *       Filename:  ShowDialog.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/12 14:56:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "GUI/ShowDialog.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "CCScale9Sprite.h"
#ifdef THIS_CLASS
#undef THIS_CLASS
#endif

#define THIS_CLASS WebGame::GUI::ShowDialog
USING_NS_CC;
USING_NS_CC_EXT;

THIS_CLASS* THIS_CLASS::create(const std::string& jsonFile) {
  using boost::property_tree::ptree;
  ptree pt;
  read_json(jsonFile, pt);

  std::string dialog = pt.get<std::string>("dialog", std::string("kddkdkdk akkdalllk"));
  std::string nineSpriteName = pt.get<std::string>("background", std::string("attack_mask.png"));
  int width = pt.get<int>("content.width", 100);
  int height = pt.get<int>("content.height", 100);
  std::string animName = pt.get<std::string>("anim", std::string(""));
  auto p = new THIS_CLASS();
  if(!p->init()) {
    p->release();
    return 0;
  }
  p->m_background = CCScale9Sprite::create(
      nineSpriteName.c_str());
  if(!p->m_background) {
    p->release();
    return 0;
  }
  p->addChild(p->m_background);
  p->m_background->setContentSize(CCSize(width, height));

  std::string fontName = pt.get<std::string>("font.name", std::string("Arial"));
  int fontSize = pt.get<int>("font.size", 24);
  p->m_label = CCLabelTTF::create(dialog.c_str(), fontName.c_str(), fontSize);
  if(!p->m_label) {
    p->release();
    return 0;
  }
  p->addChild(p->m_label);

  int labelX = pt.get<int>("label.x", 0);
  int labelY = pt.get<int>("label.y", 0);
  p->m_label->setPosition(ccp(labelX, labelY));
  int labelContaintsX = pt.get<int>("label.width", -1);
  int labelContaintsY = pt.get<int>("label.height", -1);
  if(labelContaintsX > 0 && labelContaintsY > 0) {
    p->m_label->setDimensions(CCSize(labelContaintsX, labelContaintsY));
  }

  std::string spriteFile = pt.get<std::string>("sprite.name", std::string(""));
  p->m_sprite = CCSprite::create(spriteFile.c_str());
  if(!p->m_sprite) {
    p->release();
    return 0;
  }
  int spriteX = pt.get<int>("sprite.x", 0);
  int spriteY = pt.get<int>("sprite.y", 0);
  p->m_sprite->setPosition(ccp(spriteX, spriteY));
  float anchorX = pt.get<float>("sprite.anchor_x", 0.5f);
  float anchorY = pt.get<float>("sprite.anchor_y", 0.5f);
  p->m_sprite->setAnchorPoint(ccp(anchorX, anchorY));
  float spriteScale = pt.get<float>("sprite.scale", 1.0f);
  p->m_sprite->setScale(spriteScale);
  p->addChild(p->m_sprite);

  float scale = pt.get<float>("scale", 1.0f);
  p->setScale(scale);

  p->autorelease();
  return p;
}


void THIS_CLASS::onEnter() {
  CCLog("ShowDialog onEnter");
  CCDirector::sharedDirector()->
    getTouchDispatcher()->addTargetedDelegate(this, 0, true); 
}
void THIS_CLASS::onExit() {
  CCLog("ShowDialog onExit");
  CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this); 
}
bool THIS_CLASS::ccTouchBegan(CCTouch* touch, CCEvent* event) {
  CCLog("ShowDialog ccTouchBegan");
  return true;
}
void THIS_CLASS::ccTouchMoved(CCTouch* touch, CCEvent* event) {
  CCLog("ShowDialog ccTouchMoved");

}
void THIS_CLASS::ccTouchEnded(CCTouch* touch, CCEvent* event) {
  CCLog("ShowDialog ccTouchEnded");
}
        


bool THIS_CLASS::init() {
  if(!base_class::init()) return false;
  return true;
}


#undef THIS_CLASS

