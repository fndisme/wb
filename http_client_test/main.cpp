/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/26 10:42:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <boost/network/protocol/http/client.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  using namespace boost::network;

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [url]" << std::endl;
    return 1;
  }

  http::client client;
  http::client::request request(argv[1]);
  request << header("Connection", "close");
  http::client::response response = client.get(request);
  std::cout << body(response) << std::endl;

  return 0;
}
