/*
 * =====================================================================================
 *
 *       Filename:  TileWindowPosition.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/5 18:04:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TILE_WINDOW_POSITION_H
#define FND_WEBGAME_TILE_WINDOW_POSITION_H
#include <iostream>
#include "cocos2d.h"
namespace WebGame {
  class TileWindowPosition {
    public:
      void update(int windowx, int windowy) {
        int x = windowx - m_viewSize.width / 2;
        int y = windowy - m_viewSize.height / 2;
        cocos2d::CCPoint absolutePos(m_position.x + x, m_position.y + y);
        setAbsoluteCenter(absolutePos);
      }

      void moveDelta(int deltaX, int deltaY) {
        cocos2d::CCLog("delta, %d %d", deltaX, deltaY);
        cocos2d::CCPoint pos(m_position.x + deltaX, m_position.y + deltaY);
        setAbsoluteCenter(pos);
      }

      void setAbsoluteCenter(const cocos2d::CCPoint& mapTile) {
        float x = mapTile.x;
        float y = mapTile.y;
        if(x < leftTileInPixel())
          x = leftTileInPixel();
        else if(x > rightTileInPixel()) {
          x = rightTileInPixel();
        }
        if(y < bottomTileInPixel())
          y = bottomTileInPixel();
        else if(y > topTileInPixel()) {
          y = topTileInPixel();
        }
        m_delta.x = (x - m_position.x);
        m_delta.y = (y - m_position.y);
        m_position.y = y;
        m_position.x = x;
      }

      float x() const { return  m_position.x;}
      float y() const { return  m_position.y;}
      float deltaX() const { return m_delta.x;}
      float deltaY() const { return m_delta.y;}

      float leftTileInPixel() const
      { return -(m_mapSizeInPixel.width / m_scale - m_viewSize.width)/2;}
      float rightTileInPixel() const {
        return (m_mapSizeInPixel.width / m_scale - m_viewSize.width)/2;
      }

      float bottomTileInPixel() const {
        return 0 - (m_mapSizeInPixel.height / m_scale - m_viewSize.height)/2;
      }

      float topTileInPixel() const {
        return (m_mapSizeInPixel.height / m_scale - m_viewSize.height)/2;
      }

      float initX() const { return m_initPos.x;}
      float initY() const { return m_initPos.y;}

      float windowLeft() const { return m_initPos.x - m_viewSize.width / 2.0f;}
      float windowRight() const { return m_initPos.x + m_viewSize.width / 2.0f;}
      float windowTop() const { return m_initPos.y + m_viewSize.height / 2.0f;}
      float windowBottom() const { return m_initPos.y - m_viewSize.height / 2.0f;}

      TileWindowPosition(
          const cocos2d::CCSize& mapSize,
          const cocos2d::CCSize& tileSize,
          const cocos2d::CCSize& viewSize,
          const cocos2d::CCSize& windowSize,
          const cocos2d::CCPoint& initPos,
          float scale) :
          m_mapSize(mapSize),
          m_tileSize(tileSize),
          m_viewSize(viewSize),
          m_windowSize(windowSize),
          m_mapSizeInPixel(mapSize.width * tileSize.width,
              mapSize.height * tileSize.height),
          m_initPos(initPos.x * windowSize.width, initPos.y * windowSize.height),
          m_normalizedInitPosition(initPos),
          m_scale(scale){
            cocos2d::CCLog("init pos is %f %f", m_initPos.x, m_initPos.y);
          }
      cocos2d::CCRect renderRect() const {
        return cocos2d::CCRect(mapXInPixel()/2/m_scale + x()/m_scale - m_viewSize.width / 2,
            mapYInPixel()/2/m_scale - y()/m_scale - m_viewSize.height / 2,
            m_viewSize.width, m_viewSize.height);
      }

      cocos2d::CCPoint getTilePositon(int posX, int posY) const {
//        assert(posX >= windowLeft());
//        assert(posY >= windowBottom());
//        assert(posX < windowRight());
//        assert(posY < windowTop());
        int realX = (posX + m_position.x + mapXDeltaWithWindow() - viewLeft()) / m_tileSize.width;
        int realY = (posY + m_position.y + mapYDeltaWithWindow() - viewBotton()) / m_tileSize.height;
        return ccp(realX, realY);
      }

      float realDeltaX() const { return m_position.x + mapXDeltaWithWindow() - viewLeft();}
      float realDeltaY() const { return m_position.y + mapYDeltaWithWindow() - viewBotton();}

    private:
      const cocos2d::CCSize m_mapSize;
      const cocos2d::CCSize m_tileSize;
      const cocos2d::CCSize m_viewSize;
      const cocos2d::CCSize m_windowSize;
      cocos2d::CCSize m_mapSizeInPixel;
      cocos2d::CCPoint m_position;
      cocos2d::CCPoint m_initPos;
      cocos2d::CCPoint m_normalizedInitPosition;
      cocos2d::CCPoint m_delta;
      float m_scale;
      float mapXInPixel() const { return m_mapSizeInPixel.width;}
      float mapYInPixel() const { return m_mapSizeInPixel.height;}
      float mapXDeltaWithWindow() const { return (mapXInPixel() - m_viewSize.width) / 2;}
      float mapYDeltaWithWindow() const { return (mapYInPixel() - m_viewSize.height) / 2;}
      float viewLeft() const { return (m_windowSize.width - m_viewSize.width) / 2;}
      float viewBotton() const { return (m_windowSize.height - m_viewSize.height) / 2;}

  };
}
#endif
