/*
 * =====================================================================================
 *
 *       Filename:  TestClient.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年06月02日 17时56分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_TESTCLIENT_H
#define FND_TESTCLIENT_H
#include "webgame/mock/DummyClient.h"
class TestClient : public WebGame::Mock::DummyClient {
  public:
    TestClient(boost::asio::io_service& io,
        boost::asio::strand& readStrand,
        boost::asio::strand& writeStrand,
        const std::string& init_file, WebGame::player_tt id,
        boost::mutex& mutex,
        const DecoderType& decoder
        );
  private:
    virtual bool doParse(const std::string&,
        const std::vector<std::string>&, WebGame::Message::DataBlock& db, int&);
    virtual void doInitHandler();

};
#endif

