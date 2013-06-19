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
      { return -(m_mapSizeInPixel.width - m_viewSize.width)/2;}
      float rightTileInPixel() const {
        return (m_mapSizeInPixel.width  - m_viewSize.width)/2;
      }

      float bottomTileInPixel() const {
        return 0 - (m_mapSizeInPixel.height  - m_viewSize.height)/2;
      }

      float topTileInPixel() const {
        return (m_mapSizeInPixel.height  - m_viewSize.height)/2;
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
            m_viewRect = cocos2d::CCRect(m_initPos.x - m_viewSize.width/2,
                m_initPos.y - m_viewSize.height/2,
                m_viewSize.width,
                m_viewSize.height);
            m_textureSize = cocos2d::CCSize(m_viewSize.width / m_scale, m_viewSize.height / m_scale);
          }
      cocos2d::CCRect renderRect() const {
        auto leftTop = leftTopInTexture();
      return cocos2d::CCRect(leftTop.x, leftTop.y,
            m_textureSize.width, m_textureSize.height);
      }

      cocos2d::CCPoint getObjectPosition(const cocos2d::CCPoint& pos) const {
        return getObjectPosition(pos.x, pos.y);
      }

      cocos2d::CCPoint getObjectPosition(int posX, int posY) const {
        posX = posX - m_initPos.x + m_mapSizeInPixel.width / 2;
        posY = posY - m_initPos.y + m_mapSizeInPixel.height / 2;
        return ccp(posX/m_tileSize.width, posY/m_tileSize.height);
      }

      cocos2d::CCPoint getTilePositon(int posX, int posY) const {
//        assert(posX >= windowLeft());
//        assert(posY >= windowBottom());
//        assert(posX < windowRight());
//        assert(posY < windowTop());
        cocos2d::CCPoint pos(0, 0);
        pos.x += mapXDeltaWithWindow();
        pos.y += mapYDeltaWithWindow();
        pos.x -= (viewLeft() - m_position.x) ;
        pos.y -= (viewBotton() - m_position.y) ;
        pos.x += posX;
        pos.y += posY;

        pos.x /= m_tileSize.width;
        pos.y /= m_tileSize.height;
        return pos;

      }

      cocos2d::CCPoint translateTilePositionToWindowPosition(int tileX, int tileY) const {
        cocos2d::CCPoint pos(tileX * m_tileSize.width, tileY * m_tileSize.height);
        pos.x += (viewLeft() - m_position.x)  - mapXDeltaWithWindow() + m_tileSize.width / 2;
        pos.y += (viewBotton() - m_position.y)  - mapYDeltaWithWindow() + m_tileSize.height / 2;

        return pos;
      }

      float realDeltaX() const { return m_position.x + mapXDeltaWithWindow() - viewLeft();}
      float realDeltaY() const { return m_position.y + mapYDeltaWithWindow() - viewBotton();}

    private:
      const cocos2d::CCSize m_mapSize;
      const cocos2d::CCSize m_tileSize;
      const cocos2d::CCSize m_viewSize;
      const cocos2d::CCSize m_windowSize;
      cocos2d::CCSize m_textureSize;
      cocos2d::CCRect m_viewRect;
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
      cocos2d::CCPoint leftTopInTexture() const {
        return ccp((mapXInPixel()/2 + x())/m_scale - m_textureSize.width/2,
            (mapYInPixel()/2 - y())/m_scale - m_textureSize.height/2);
      }

  };
}
#endif
