#ifndef FND_GAME_MESSAGE_H
#define FND_GAME_MESSAGE_H
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
#include <stdexcept>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <memory>
#ifndef _WIN32
#include <folly/Optional.h>
#endif
#include "webgame/message/Header.pb.h"
#include "webgame/shared/Platform.h"
#include "webgame/shared/identity_type.h"
namespace WebGame {
  namespace Message {
  class MessageBuilder ;

  class DataBlock {
  public:
    typedef MessageBuilder DecoderType ;
    typedef WebGame::player_tt IdentityType ;
    static IdentityType system_identity() { return IdentityType(0) ;}
    class Error : public std::runtime_error {
    public:
      enum error_reason_t { BUFFER_SIZE_ERROR = 0,
                            PROTOBUFFER_PACK_ERROR = 1,
                            PROTOBUFFER_IMPORT_ERROR = 2,
      } ;
      Error(const char* info, error_reason_t error_reason) :
        runtime_error(info),
        m_reason(error_reason) {}
      error_reason_t reason() const { return m_reason ;}
      const error_reason_t m_reason ;
    } ;
    typedef std::shared_ptr< ::google::protobuf::Message> body_type ;
    typedef DataExchange::Header header_type ;
    DataBlock() ;
    ~DataBlock() ;
    template<typename T>
      explicit DataBlock(std::shared_ptr<T> msg,
					WebGame::player_tt pid = WebGame::player_tt(0)) {
          setHeaderId(pid) ;
          setBody(msg) ;
        }
		template<typename T>
      explicit DataBlock(std::unique_ptr<T>&& msg,
					WebGame::player_tt pid = WebGame::player_tt(0)) {
          setHeaderId(pid) ;
          setBody(std::move(msg)) ;
        }
    DataBlock(int type,
            DecoderType const& builder,
            const void* body_data, size_t body_size,
        WebGame::player_tt = WebGame::player_tt(0)) ;

    static std::string describeHeaderInformation(const DataBlock& db) ;

    std::shared_ptr< ::google::protobuf::Message>
    body() const {return m_body ;}

    std::shared_ptr< ::google::protobuf::Message>
    body() {return m_body ;}


		template<typename T>
			std::shared_ptr<const T> constBody() const {
				return std::static_pointer_cast<const T>(m_body) ;
			}
		template<typename T>
			const T& constRefBody() const {
				return *(std::static_pointer_cast<const T>(m_body)) ;
			}
    inline
    WebGame::player_tt headerId() const { return WebGame::player_tt(m_header.id()) ;}
    inline
    int messageType() const {return m_header.type() ;}
    inline
    void setHeaderId(int id) { m_header.set_id(id) ;}
    inline void debugSetSize(int s) { m_header.set_size(s) ;}
    inline
    void setHeaderId(WebGame::player_tt id) { m_header.set_id(id.base_type_value()) ;}
    template<typename T>
    void setBody(std::shared_ptr<T> nb) {
      setBody(T::value, nb) ;
    }
		template<typename T>
			void setBody(std::unique_ptr<T>&& nb) {
				std::shared_ptr<T> msg(nb.release()) ;
				setBody(msg) ;
			}
    size_t totalSize() const  ;
    static CONSTEXPR size_t headerSize() {return 4+4+4+3 ; }//id(4) + type(4) + size(4) + 3
    size_t bodySize()const ;
    bool packToArray(void *buffer, size_t buffer_size) const ;
    bool packToVector(std::vector<char>&) const ;
    bool packHeaderToArray(void* buffer, size_t header_size) const ;
#ifndef _WIN32
    typedef folly::Optional<std::string> StringBlob ;
    StringBlob packToString() const ;
#endif
    bool packToString(std::string&) const ;

    bool importFromArray(const void* buffer, size_t buffer_size, DecoderType const&) ;
    bool importFromString(const std::string&, DecoderType const&) ;
    bool importBodyFromString(int id, const std::string&, DecoderType const&) ;
    bool importBodyFromString(const std::string&, DecoderType const&) ;
    bool importHeaderFromArray(const void* buffer, size_t buffer_size) ;
    bool importBodyFromArray(const void* buffer,
        size_t buffer_size, DecoderType const&) ;
    bool importHeaderFromArray(const std::vector<char>& vec) ;
    bool importBodyFromArray(const std::vector<char>& vec, DecoderType const&) ;
    bool importHeaderFromString(const std::string&) ;
    DataBlock& operator = (const DataBlock& db) ;
    DataBlock& operator = (DataBlock&& db) ;
    DataBlock(DataBlock&& rhs) ;
    DataBlock(const DataBlock& db) ;
		std::string debugString() const ;

  private:

    header_type& header() { return m_header ;}
    const header_type& header() const {
      return m_header ;}
    header_type m_header ;
    std::shared_ptr< ::google::protobuf::Message> m_body ;
    void setBody(int type, body_type new_body) ;
    bool safeBuildBody(const void*, size_t, DecoderType const&) ;
    bool safeBuildBody(int, const void*, size_t, DecoderType const&) ;
    bool safeBuildBody(int, const std::string& data, DecoderType const&);
		template<typename T>
    std::shared_ptr<T> body() const {
      return std::static_pointer_cast<T>(m_body) ;
    }
    void sync() ;
  public:
    bool isSync() const ;

  } ;
  }
}

#endif
