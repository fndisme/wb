/*
 * =====================================================================================
 *
 *       Filename:  DataCache_fwd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-1 11:35:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef	FND_WEBGAME_DATACACHE_FWD_H
#define FND_WEBGAME_DATACACHE_FWD_H
#include	<memory>
namespace WebGame {
  namespace Message {
	class DataCache ;
	typedef std::shared_ptr<const DataCache> DataCachePointer ;
  }
}

#endif
