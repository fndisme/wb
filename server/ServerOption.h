/*
 * =====================================================================================
 *
 *       Filename:  ServerOption.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-6 10:55:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVEROPTION_H
#define FND_WEBGAME_SERVEROPTION_H
#include <string>
#include <boost/noncopyable.hpp>
#include "webgame/server/ZSocketDef.h"
namespace WebGame {
  namespace Server {

      template<typename MessageDecoder>
    struct ServerOption : boost::noncopyable {
      boost::asio::io_service* IoService ;
      QSocketTratis::context_t* ZeroContext ;
      const std::string PropertyFileName ;
      boost::asio::strand* ReadStrand;
      boost::asio::strand* WriteStrand;
      MessageDecoder* Decoder;
      explicit ServerOption(
          const std::string& filename,
          boost::asio::io_service* service = nullptr,
          QSocketTratis::context_t* context = nullptr,
          MessageDecoder* decoder= nullptr,
          boost::asio::strand* readStrand = nullptr,
          boost::asio::strand* writeStrand = nullptr) :
        IoService(service),
        ZeroContext(context),
        PropertyFileName(filename),
        ReadStrand(readStrand),
        WriteStrand(writeStrand),
        Decoder(decoder){}
    } ;
  }

}
#endif
