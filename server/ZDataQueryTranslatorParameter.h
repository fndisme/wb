/*
 * =====================================================================================
 *
 *       Filename:  ZDataQueryTranslatorParameter.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-21 10:22:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZDATAQUERY_TRANSLATORPARAMETER_H
#define FND_WEBGAME_ZDATAQUERY_TRANSLATORPARAMETER_H
#include <tuple>
#include "data_block_fwd.h"

namespace WebGame
{
typedef std::tuple<int, const Fnd::data_block&, Fnd::data_block&> ZDataQueryTranslatorParameter ;
}

#endif
