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
#include "ZSocketDef.h"
namespace WebGame
{
struct ServerOption {
    boost::asio::io_service* IoService ;
    QSocketTratis::context_t* ZeroContext ;
    const std::string PropertyFileName ;

    explicit ServerOption(
        const std::string& filename,
        boost::asio::io_service* service = nullptr,
        QSocketTratis::context_t* context = nullptr) :
        IoService(service),
        ZeroContext(context),
        PropertyFileName(filename) {}
    ServerOption(ServerOption const&) = default ;
    ServerOption& operator = (ServerOption const&) = default ;
} ;

}
#endif
