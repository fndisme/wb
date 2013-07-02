/*
 * =====================================================================================
 *
 *       Filename:  ClientSet.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/25 9:31:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SERVER_CLIENTSET_H
#define FND_WEBGAME_SERVER_CLIENTSET_H
#include <memory>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include "webgame/shared/identity_type.h"

namespace WebGame {
  namespace Server {
    template<typename T>
      struct sortByConnection {
        typedef typename T::ConnectionType result_type ;
        result_type operator()(const std::shared_ptr<T>& p) const {
          return p->connection();
        }
      } ;

    template<typename T>
      struct sortById {
        typedef typename T::IdType result_type ;
        result_type operator()(const std::shared_ptr<T>& p) const {
          return p->id();
        }
      } ;

   template<typename T>
      struct sortBySession {
        typedef typename T::SessionType result_type ;
        result_type operator()(const std::shared_ptr<T>& p) const {
          return p->session();
        }
      } ;
  }
}
#endif
