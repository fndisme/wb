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
#include <algorithm>
#include <functional>
using namespace cocos2d;

namespace WebGame {
  TileMask*
    TileMask::create(cocos2d::CCTexture2D* tex,
        const cocos2d::CCPoint& pos,
        const cocos2d::CCPoint& mapPos,
        const cocos2d::CCSize& tileSize,
        float scale,
        std::vector<cocos2d::CCPoint>&& tilepos) {
      TileMask* mask = new TileMask();
      mask->m_mapPosition = mapPos;
      mask->m_tilePositions = std::move(tilepos);
      mask->autorelease();
      mask->setPosition(pos);
      mask->setAnchorPoint(ccp(0.0,0.0));

      for(int i = 0 ; i < mask->m_tilePositions.size() ; ++i) {
        CCSprite* s = CCSprite::createWithTexture(tex);
        s->setPosition(ccp(mask->m_tilePositions[i].x * tileSize.width,
              mask->m_tilePositions[i].y * tileSize.height));
        s->setAnchorPoint(ccp(0.0f,0.0f));
        s->setScale(scale);
        mask->addChild(s);
      }
      return mask;
    }

  bool TileMask::hasPosition(const cocos2d::CCPoint& pos) const {
    CCPoint findPos(pos.x - m_mapPosition.x, pos.y - m_mapPosition.y);
    bool ok = std::find_if(m_tilePositions.begin(), m_tilePositions.end(),
        [&findPos](const CCPoint& p)
        { return p.x == findPos.x && p.y == findPos.y ;}) != m_tilePositions.end();
    return ok;
  }


}
