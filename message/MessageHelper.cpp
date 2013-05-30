#include "webgame/message/MessageHelper.h"

namespace WebGame {
  namespace Message {
  using std::shared_ptr ;
  using namespace game_connection ;
  bool pack_group_message(shared_ptr<pack_group> pg, const DataBlock& db) {
    std::string infomation ;
    if(db.packToString(infomation)) {
      game_connection::pack_group_pack_type* pgpt = pg->add_pack() ;
      pgpt->set_type(0) ;
      pgpt->set_infomation(infomation) ;
      return true ;
    }
    return false ;

  }

  bool pack_group_message(shared_ptr<pack_group> pg, int type,
                          const std::string& infomation) {
    game_connection::pack_group_pack_type* pgpt = pg->add_pack() ;
    pgpt->set_type(type) ;
    pgpt->set_infomation(infomation) ;
    return true ;
  }

  DataBlock extrack_group_message(shared_ptr<const pack_group> pg, size_t position,
                                   WebGame::player_tt pid) {
    const game_connection::pack_group_pack_type& pk = pg->pack(position) ;
    DataBlock db ;
    if(pk.type() == 0) {
      db.importFromString(pk.infomation()) ;
    } else {
      db.setHeaderId(pid) ;
      db.importBodyFromString(pk.type(), pk.infomation()) ;
    }
    return db ;
  }
  }
}
