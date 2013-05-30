/*
 * =====================================================================================
 *
 *       Filename:  ServerDef.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-9 13:26:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVERDEF_H
#define FND_WEBGAME_SERVERDEF_H
#include <stlsoft/util/true_typedef.hpp>
namespace WebGame
{
STLSOFT_GEN_OPAQUE(h_searching_team_tt)

typedef stlsoft::true_typedef<int, h_searching_team_tt> searching_team_tt ;
enum class RewardType
{
    Fight,
    Dig,
    SingleInstance,
    Online,
    RoundInstance,
    DailyBoss,
    DailyBossBonus,
    WhipCorpse,
    WhipRank,
    Summon,
    VipSweepAway,
    NormalSweepAway,
    ActiveRecharging,
    PositiveRecharging,
} ;

}
#endif
