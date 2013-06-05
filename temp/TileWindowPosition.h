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
namespace WebGame {
  struct Size {
    int Width;
    int Height;
    explicit Size(int w = 0, int h = 0) : Width(w), Height(h) {} 
  };
  struct Position {
    int X;
    int Y;
    explicit Position(int x = 0, int y = 0) : X(x), Y(y) {}
  };
  class TileWindowPosition {
    public:
      update(int windowx, int windowy) {
        int x = windowx - m_windowSize.Width / 2;
        int y = windowy - m_windowSize.Height / 2;
        Position absolutePos(m_position.X + x, m_position.Y + y);
        setAbsoluteCenter(absolutePos);
      }

      moveDelta(int deltaX, int deltaY) {
        Position pos(m_position.X + deltaX, m_position.Y + deltaY);
        setAbsoluteCenter(pos);
      }

      Position tilePosition(Position const& tile) const {
        int x = tile.X * m_tileSize.Width + m_tileSize.Width / 2;
        int y = tile.Y * m_tileSize.Height + m_tileSize.Width / 2;
        x -= m_position.X;
        y -= m_position.Y;

      }

      setAbsoluteCenter(const Position& mapTile) {
        int x = mapTile.X;
        int y = mapTile.Y;
        if(x < leftTileInPixel())
          x = leftTileInPixel();
        else if(x > rightTileInPixel())
          x = rightTileInPixel;
        if(y < bottomTileInPixel())
          y = bottomTileInPixel();
        else if(y > topTileInPixel())
          y = topTileInPixel();
        
        m_position.X = x;
        m_position.Y = y;
      }

      int leftTileInPixel() const
      { return 0;}
      int rightTileInPixel() const {
        return m_mapSizeInPixel.Width - m_windowSize.Width;
      }

      int bottomTileInPixel() const {
        return 0;
      }

      int topTileInPixel() const {
        return m_mapSizeInPixel.Height - m_windowSize.Height;
      }

      TileWindowPosition(
          const Size& mapSize,
          const Size& tileSize,
          const Size& windowSize) :
          m_mapSize(mapSize),
          m_tileSize(tileSize),
          m_windowSize(windowSize),
          m_mapSizeInPixel(mapSize.Width * tileSize.Width,
              mapSize.Height * tileSize.Height) {}

    private:
      const Size m_mapSize;
      const Size m_tileSize;
      const Size m_windowSize;
      Size m_mapSizeInPixel;
      Position m_position;
  
  };
}
#endif
