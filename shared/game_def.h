#ifndef FND_WEBGAME_GAME_DEF_H
#define FND_WEBGAME_GAME_DEF_H
#include <array>
#include "identity_type.h"
namespace WebGame {
  enum server_limits {
    player_max_money_type = 5,
  } ;
  typedef std::tr1::array<money_tt, player_max_money_type> player_money_group_type ;
}
#endif
