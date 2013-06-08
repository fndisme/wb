/*
 * =====================================================================================
 *
 *       Filename:  TileMask.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/8 16:48:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "TileMask.h"
using namespace cocos2d;

namespace WebGame {
  TileMask*
    TileMask::create(cocos2d::CCTexture2D* tex,
        const cocos2d::CCPoint& pos,
        const cocos2d::CCPoint& mapPos,
        const cocos2d::CCSize& tileSize,
        const std::vector<cocos2d::CCPoint>& tilepos) {
      TileMask* mask = new TileMask();
      mask->autorelease();
      mask->setPosition(pos);

      int deltaX = pos.x - mapPos.x;
      int deltaY = pos.y - mapPos.y;
      for(int i = 0 ; i < tilepos.size() ; ++i) {
        CCSprite* s = CCSprite::createWithTexture(tex);
        s->setPosition(ccp(tilepos[i].x * tileSize.width - mapPos.x,
              tilepos[i].y * tileSize.height - mapPos.y));
        s->setAnchorPoint(ccp(0,0));
        mask->addChild(s);
      }
      return mask;
    }
}
