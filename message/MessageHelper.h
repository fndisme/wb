#ifndef FND_MESSAGEHELPER_H
#define FND_MESSAGEHELPER_H
#include <string>
#include <memory>
#include "webgame/shared/identity_type.h"
#include "webgame/message/pack_group_message.pb.h"
#include "webgame/message/DataBlock.h"
namespace WebGame {
  namespace Message {
  typedef std::shared_ptr<game_connection::pack_group> pack_group_pointer ;
  bool pack_group_message(std::shared_ptr<game_connection::pack_group> pg,
                          const DataBlock& db) ;



  template<typename T>
  bool pack_group_message(std::shared_ptr<game_connection::pack_group> pg,
                          const T& msg) {
    std::string infomation ;
    if(msg.SerializeToString(&infomation)) {
      game_connection::pack_group_pack_type* pgpt = pg->add_pack() ;
      pgpt->set_type(T::value) ;
      pgpt->set_infomation(infomation) ;
      return true ;
    }
    return false ;
  }

  bool pack_group_message(std::shared_ptr<game_connection::pack_group> pg,
                          int type, const std::string&) ;


  template<typename T>
  bool pack_group_message(std::shared_ptr<game_connection::pack_group> pg,
                          std::shared_ptr<T> msg) {
    std::string infomation ;
    if(msg->SerializeToString(&infomation)) {
      game_connection::pack_group_pack_type* pgpt = pg->add_pack() ;
      pgpt->set_type(T::value) ;
      pgpt->set_infomation(infomation) ;
      return true ;
    }
    return false ;
  }

  DataBlock extrack_group_message(std::shared_ptr<const game_connection::pack_group> pg,
                                   size_t i, WebGame::player_tt pid) ;

  }
}
#endif
