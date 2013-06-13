/*
 * =====================================================================================
 *
 *       Filename:  Terrain.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/13 16:48:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TERRAIN_H
#define FND_WEBGAME_TERRAIN_H
namespace WebGame {
  struct Terrain {
      int Water;
      int Fire;
      int Wind;
      int Ice;
      int Attack;
      int Defence;
      int Speed;
      int MovePower;
  };
}
#endif
