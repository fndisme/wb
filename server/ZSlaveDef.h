/*
 * =====================================================================================
 *
 *       Filename:  ZSlaveDef.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年04月05日 15时26分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSLAVEDEF_H
#define FND_WEBGAME_ZSLAVEDEF_H
#include <string>
#include <boost/flyweight.hpp>
namespace WebGame {
  typedef boost::flyweight<std::string> SlaveServerNameType ;
}

#endif

