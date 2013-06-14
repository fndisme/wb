/*
 * =====================================================================================
 *
 *       Filename:  Evaluation.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/13 20:21:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_EVALUATION_H
#define FND_WEBGAME_EVALUATION_H
namespace WebGame {
  
  // from Fire Emblem I think so.
  int attackSpeed(int speed, int bodyPower, int weaponWeight);
  int attackTimes(int lhsAttackSpeed, int rhsAttackSpeed);



}

#endif

