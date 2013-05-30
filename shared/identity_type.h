#ifndef IDENTITY_TYPE_H
#define IDENTITY_TYPE_H
#include <cstdint>
#include <stlsoft/util/true_typedef.hpp>
#ifdef USE_FOLLY
#include <folly/Traits.h>
#endif


namespace WebGame {
  STLSOFT_GEN_OPAQUE(h_player_tt)
  STLSOFT_GEN_OPAQUE(h_mail_tt)
  STLSOFT_GEN_OPAQUE(h_money_tt)
  STLSOFT_GEN_OPAQUE(h_sell_tt)
  STLSOFT_GEN_OPAQUE(h_meta_tt)
  STLSOFT_GEN_OPAQUE(h_level_tt)
  STLSOFT_GEN_OPAQUE(h_equipment_tt)
  STLSOFT_GEN_OPAQUE(h_bag_tt)
  STLSOFT_GEN_OPAQUE(h_page_tt)
  STLSOFT_GEN_OPAQUE(h_cell_tt)
  STLSOFT_GEN_OPAQUE(h_net_connection_tt)
  STLSOFT_GEN_OPAQUE(h_task_tt)
  STLSOFT_GEN_OPAQUE(h_score_tt)
  STLSOFT_GEN_OPAQUE(h_match_tt)
	STLSOFT_GEN_OPAQUE(h_prop_tt)
	STLSOFT_GEN_OPAQUE(h_times_tt)
	STLSOFT_GEN_OPAQUE(h_second_tt)
	STLSOFT_GEN_OPAQUE(h_fleet_type)
  STLSOFT_GEN_OPAQUE(h_world_tt)
  STLSOFT_GEN_OPAQUE(h_group_tt)
  STLSOFT_GEN_OPAQUE(h_message_tt)
  STLSOFT_GEN_OPAQUE(h_size_tt)
  STLSOFT_GEN_OPAQUE(h_ticket_tt)
  STLSOFT_GEN_OPAQUE(h_war_tt)
  STLSOFT_GEN_OPAQUE(h_challenge_rank_tt)
  STLSOFT_GEN_OPAQUE(h_grade_tt)
		STLSOFT_GEN_OPAQUE(h_map_type)

		typedef stlsoft::true_typedef<int, h_map_type> map_tt ;
  typedef stlsoft::true_typedef<std::int32_t, h_challenge_rank_tt> challenge_rank_tt ;
  typedef stlsoft::true_typedef<int, h_grade_tt> grade_tt ;
  typedef stlsoft::true_typedef<int, h_war_tt> war_tt ;
  typedef stlsoft::true_typedef<std::int32_t, h_group_tt> group_tt ;
  typedef stlsoft::true_typedef<std::uint32_t, h_message_tt> message_tt ;
  typedef stlsoft::true_typedef<std::uint32_t, h_size_tt> size_tt ;
  typedef stlsoft::true_typedef<int, h_world_tt> world_tt ;
	typedef stlsoft::true_typedef<int, h_fleet_type> fleet_tt ;
	typedef stlsoft::true_typedef<long, h_second_tt> second_tt ;
	typedef stlsoft::true_typedef<int, h_times_tt> times_tt ;
  typedef stlsoft::true_typedef<int, h_ticket_tt> ticket_tt ;
  typedef stlsoft::true_typedef<size_t, h_match_tt> match_tt ;
  typedef stlsoft::true_typedef<long, h_score_tt> score_tt ;
  typedef stlsoft::true_typedef<size_t, h_task_tt> task_tt ;
  typedef stlsoft::true_typedef<size_t, h_net_connection_tt> net_connection_tt ;
  typedef stlsoft::true_typedef<size_t, h_bag_tt> bag_tt ;
  typedef stlsoft::true_typedef<size_t, h_page_tt> page_tt ;
  typedef stlsoft::true_typedef<size_t, h_cell_tt> cell_tt ;
  typedef stlsoft::true_typedef<int, h_equipment_tt> equipment_tt ;
	typedef stlsoft::true_typedef<int, h_prop_tt> prop_tt ;
  typedef stlsoft::true_typedef<unsigned int, h_level_tt> level_tt ;
  typedef stlsoft::true_typedef<std::int32_t, h_player_tt> player_tt ;
  typedef stlsoft::true_typedef<int, h_mail_tt> mail_tt ;
  typedef stlsoft::true_typedef<long long int, h_money_tt> money_tt ;
  typedef stlsoft::true_typedef<int, h_sell_tt> sell_tt ;
  typedef stlsoft::true_typedef<int, h_meta_tt> meta_tt ;
}

#ifdef USE_FOLLY
FOLLY_ASSUME_FBVECTOR_COMPATIBLE(WebGame::player_tt)
#endif

#endif
