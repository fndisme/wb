/*
 * =====================================================================================
 *
 *       Filename:  TileMask.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/8 16:25:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TILEMASK_H
#define FND_WEBGAME_TILEMASK_H
#include <vector>
#include "cocos2d.h"

namespace WebGame {
  class TileMask : public cocos2d::CCNode {
    public:
      static TileMask*
        create(cocos2d::CCTexture2D* tex,
            const cocos2d::CCPoint& pos,
            const cocos2d::CCPoint& mapPos,
            const cocos2d::CCSize& tileSize,
            float scale,
            std::vector<cocos2d::CCPoint>&& tilepos);
      bool hasPosition(const cocos2d::CCPoint& pos) const;
    private:
      cocos2d::CCPoint m_mapPosition;
      std::vector<cocos2d::CCPoint> m_tilePositions;
  };
}
#endif
