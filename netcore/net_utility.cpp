#include "net_utility.h"
#include  <boost/asio/impl/src.hpp> 
#include <stlsoft/memory/auto_buffer.hpp>
#include	"webgame/message/DataBlock.h"
#include "webgame/message/DataCache.h"

namespace WebGame {
  bool readSyncMessage(boost::asio::ip::tcp::socket& socket,
                                       Message::DataBlock& db) {
    typedef stlsoft::auto_buffer<char, 1024> buffer_t ;
    buffer_t buf(db.headerSize()) ;
    boost::asio::read(socket,
                      boost::asio::buffer(&buf[0],
                                          Message::DataBlock::headerSize()),
                      boost::asio::transfer_all()) ;
    if(!db.importHeaderFromArray(static_cast<const void*>(&buf[0]),
          Message::DataBlock::headerSize()))
      return false ;
    buf.resize(db.bodySize()) ;
    boost::asio::read(socket,
                      boost::asio::buffer(&buf[0], db.bodySize()),
                      boost::asio::transfer_all()) ;
    return db.importBodyFromArray(static_cast<const void*>(&buf[0]), db.bodySize()) ;
  }
  bool readSyncMessage(boost::asio::ip::tcp::socket& socket,
                                       Message::DataBlock& db,
                                       boost::system::error_code& error) {
    typedef stlsoft::auto_buffer<char, 1024> buffer_t ;
    buffer_t buf(db.headerSize()) ;
 
    boost::asio::read(socket,
                      boost::asio::buffer(&buf[0],
                                          Message::DataBlock::headerSize()),
                      boost::asio::transfer_all(),
                      error) ;
    if(error ||
        !db.importHeaderFromArray(static_cast<const void*>(&buf[0]),
          Message::DataBlock::headerSize()))
      return false ;
    buf.resize(db.bodySize()) ;
    boost::asio::read(socket,
                      boost::asio::buffer(&buf[0],
                                          db.bodySize()),
                      boost::asio::transfer_all(),
                      error) ;
    if(error) return false ;
    return  db.importBodyFromArray(static_cast<const void*>(&buf[0]), db.bodySize()) ;
  }

}
    
