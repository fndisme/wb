#include "webgame/message/DataBlock.h"
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include	<pantheios/inserters/i.hpp>
#include	<fastformat/fastformat.hpp>
#include <boost/config/warning_disable.hpp>
#include <pantheios/assert.h>
#include "webgame/message/MessageBuilder.h"



namespace WebGame {
  namespace Message {
  DataBlock& DataBlock::operator = (const DataBlock& db) {
    if(this == &db) return *this ;
    m_header = db.header() ;
    m_body = db.body() ;
    return *this ;
  }

  DataBlock& DataBlock::operator = (DataBlock&& db) {
    if(this == &db) return *this ;
    m_header = db.m_header ;
    db.m_header.Clear() ; // not used any more
    m_body = std::move(db.m_body) ;
    return *this ;
  }


  DataBlock::DataBlock(const DataBlock& db) : m_header(db.header()),
	m_body(db.body()) {
	}

  DataBlock::DataBlock(DataBlock&& lhs) :
    m_header(lhs.header()),
  m_body(std::move(lhs.m_body)) {
    lhs.m_header.Clear() ; // not valid any more
  }

  DataBlock::~DataBlock() {}

#ifndef _WIN32
  DataBlock::StringBlob DataBlock::packToString() const {
    std::string sink ;
    if(!m_header.SerializeToString(&sink)) return StringBlob() ;
    std::string sink2 ;
    if(!m_body->SerializeToString(&sink2)) return StringBlob() ;
    PANTHEIOS_ASSERT((sink.size() + sink2.size()) == totalSize()) ;
    return sink + sink2 ;
  }
#endif

  bool DataBlock::packToString(std::string& sink) const {
    if(!m_header.SerializeToString(&sink)) return false ;
    std::string sink2 ;
    if(!m_body->SerializeToString(&sink2)) return false ;
    sink += sink2 ;
    PANTHEIOS_ASSERT(sink.size() == totalSize()) ;
    return true ;
  }

  bool DataBlock::packToVector(std::vector<char>& vec) const {
    vec.resize(totalSize()) ;
    return  packToArray(&vec[0], vec.size()) ;
  }

  /*static */
  std::string DataBlock::describeHeaderInformation(const DataBlock& db) {
		std::string sink ;
		fastformat::fmt(sink, "Header info is:{0}", db.m_header.DebugString()) ;
    return sink;
  }

  size_t DataBlock::totalSize() const{
    PANTHEIOS_ASSERT(m_body) ;
    PANTHEIOS_ASSERT(isSync()) ;
    return headerSize() + bodySize() ;
  }

  size_t DataBlock::bodySize() const{
    return header().size() ;
  }


  void DataBlock::setBody(int type, body_type new_body) {
    m_body = new_body ;
    m_header.set_type(type) ;
    m_header.set_size(m_body->ByteSize()) ;

  }

  DataBlock::DataBlock(int body_type,
          DecoderType const& builder,
          const void* buffer_data,
      size_t buffer_size, WebGame::player_tt pid) {
    m_header.set_type(body_type) ;
    m_header.set_id(pid.base_type_value()) ;

    bool ok = safeBuildBody(body_type, buffer_data, buffer_size, builder) ;
    if(!ok) {
      throw Error("Create DataBlock failed.... ", Error::PROTOBUFFER_IMPORT_ERROR) ;
    }
    m_header.set_size(m_body->ByteSize()) ;
  }

  DataBlock::DataBlock()  {
    m_header.set_type(0) ;
    m_header.set_size(0) ;
    m_header.set_id(0) ;
  }

  bool DataBlock::isSync() const {
    return m_header.type() != 0 &&
      (m_body.get() ?
       static_cast<int>(m_header.size()) == m_body->ByteSize() : true) ;
  }

  void DataBlock::sync() {
    m_header.set_size(m_body->ByteSize()) ;
  }

  bool DataBlock::packToArray(void* buffer, size_t buffer_size)const {
		return buffer &&
			buffer_size >= totalSize() &&
			packHeaderToArray(buffer, headerSize()) &&
			m_body->SerializeToArray((void*)((char*)buffer + headerSize()), bodySize()) ;
  }



  bool DataBlock::packHeaderToArray(void* buffer, size_t buffer_size) const {
    if(!buffer) return false ;
    if(buffer_size < DataBlock::headerSize()) return false ;
    //m_header.set_size(m_body->ByteSize()) ;
    return m_header.SerializeToArray(buffer, headerSize()) ;
  }


  bool DataBlock::importHeaderFromArray(const std::vector<char>& vec) {
    if(vec.size() < headerSize()) return false ;
    return m_header.ParseFromArray(&vec[0], headerSize()) ;
  }

    bool DataBlock::importFromArray(const void* b, size_t buffer_size,
      DecoderType const& builder) {
    if(buffer_size < headerSize()) return false ;
    if(!importHeaderFromArray(b, headerSize())) return false ;
    return importBodyFromArray((const void*)((const char*)b + headerSize()),
                                  buffer_size - headerSize(),
                                  builder) ;
  }


  bool DataBlock::importHeaderFromArray(const void* buffer, size_t buffer_size) {

    if(!buffer || buffer_size < headerSize()) return false ;

    return m_header.ParseFromArray(buffer, headerSize()) ;

  }

  bool DataBlock::importBodyFromString(int type, const std::string& buffer,
          DecoderType const& builder) {
    if(!safeBuildBody(type, buffer, builder)) return false ;
    m_header.set_type(type) ;
    m_header.set_size(m_body->GetCachedSize()) ;
    return true ;
  }

  bool DataBlock::importHeaderFromString(const std::string& header) {
    return m_header.ParseFromString(header) ;
  }

  bool DataBlock::importBodyFromString(const std::string& buffer,
          DecoderType const& builder) {
    PANTHEIOS_ASSERT(m_header.type() != 0) ;
    return importBodyFromString(m_header.type(), buffer, builder) ;
  }

  bool DataBlock::importFromString(const std::string& buffer,
          const DecoderType& builder) {
    // I know this is a bug. Just try.........
    return importFromArray(buffer.data(), buffer.size(), builder) ;
  }


  bool DataBlock::safeBuildBody(const void* buffer, size_t buffer_size,
      DataBlock::DecoderType const& builder) {
    return safeBuildBody(m_header.type(), buffer, buffer_size, builder) ;
  }

  bool DataBlock::safeBuildBody(int type, const std::string& v,
      DataBlock::DecoderType const& builder) {
    return safeBuildBody(type, v.data(), v.size(), builder) ;
  }




  bool DataBlock::safeBuildBody(int type, const void* buffer, size_t buffer_size,
      DataBlock::DecoderType const& builder) {
    bool ok = false ;
    try {

      auto newblock = builder.buildMessage(m_header.type()) ;
      ok = newblock->ParseFromArray(buffer, buffer_size) &&
        static_cast<size_t>(newblock->ByteSize()) == buffer_size ;
      if(!ok) {
        pantheios::log_WARNING("message infomation is not right",
            pantheios::integer(type)) ;
      } else {
        m_body = std::move(newblock) ;
      }
    } catch(...) {
      return false ;
    }

    return ok ;
  }


  std::string DataBlock::debugString() const {
      if(m_body) {
          std::string sink ;
          fastformat::fmt(sink, "H:\t{0}\nbody:\t{1}",
                  m_header.ShortDebugString(),
                  m_body->ShortDebugString()) ;
          return sink ;
      } else {
          return std::string("[not valid DataBlock....]") ;
      }
  }

  bool DataBlock::importBodyFromArray(const std::vector<char>& vec,
          DecoderType const& builder) {
    size_t bs = m_header.size() ;
    return vec.size() >= bs && safeBuildBody(vec.data(), bs, builder) ;

  }
  bool DataBlock::importBodyFromArray(const void* b,
      size_t buffer_size,
      DecoderType const& builder) {
    size_t bs = m_header.size() ;
    return buffer_size >= bs && safeBuildBody(b, bs, builder) ;
  }

  }
}
