// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: QueryHallPlayerIdList.proto

#ifndef PROTOBUF_QueryHallPlayerIdList_2eproto__INCLUDED
#define PROTOBUF_QueryHallPlayerIdList_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace game_connection {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_QueryHallPlayerIdList_2eproto();
void protobuf_AssignDesc_QueryHallPlayerIdList_2eproto();
void protobuf_ShutdownFile_QueryHallPlayerIdList_2eproto();

class QueryHallPlayerIdList;

enum QueryHallPlayerIdList_traits {
  QueryHallPlayerIdList_traits_value = 4319
};
bool QueryHallPlayerIdList_traits_IsValid(int value);
const QueryHallPlayerIdList_traits QueryHallPlayerIdList_traits_traits_MIN = QueryHallPlayerIdList_traits_value;
const QueryHallPlayerIdList_traits QueryHallPlayerIdList_traits_traits_MAX = QueryHallPlayerIdList_traits_value;
const int QueryHallPlayerIdList_traits_traits_ARRAYSIZE = QueryHallPlayerIdList_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* QueryHallPlayerIdList_traits_descriptor();
inline const ::std::string& QueryHallPlayerIdList_traits_Name(QueryHallPlayerIdList_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    QueryHallPlayerIdList_traits_descriptor(), value);
}
inline bool QueryHallPlayerIdList_traits_Parse(
    const ::std::string& name, QueryHallPlayerIdList_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<QueryHallPlayerIdList_traits>(
    QueryHallPlayerIdList_traits_descriptor(), name, value);
}
// ===================================================================

class QueryHallPlayerIdList : public ::google::protobuf::Message {
 public:
  QueryHallPlayerIdList();
  virtual ~QueryHallPlayerIdList();
  
  QueryHallPlayerIdList(const QueryHallPlayerIdList& from);
  
  inline QueryHallPlayerIdList& operator=(const QueryHallPlayerIdList& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const QueryHallPlayerIdList& default_instance();
  
  void Swap(QueryHallPlayerIdList* other);
  
  // implements Message ----------------------------------------------
  
  QueryHallPlayerIdList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const QueryHallPlayerIdList& from);
  void MergeFrom(const QueryHallPlayerIdList& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef QueryHallPlayerIdList_traits traits;
  static const traits value = QueryHallPlayerIdList_traits_value;
  static inline bool traits_IsValid(int value) {
    return QueryHallPlayerIdList_traits_IsValid(value);
  }
  static const traits traits_MIN =
    QueryHallPlayerIdList_traits_traits_MIN;
  static const traits traits_MAX =
    QueryHallPlayerIdList_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    QueryHallPlayerIdList_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return QueryHallPlayerIdList_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return QueryHallPlayerIdList_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return QueryHallPlayerIdList_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 hall_id = 1;
  inline bool has_hall_id() const;
  inline void clear_hall_id();
  static const int kHallIdFieldNumber = 1;
  inline ::google::protobuf::int32 hall_id() const;
  inline void set_hall_id(::google::protobuf::int32 value);
  
  // optional int32 hall_type = 2;
  inline bool has_hall_type() const;
  inline void clear_hall_type();
  static const int kHallTypeFieldNumber = 2;
  inline ::google::protobuf::int32 hall_type() const;
  inline void set_hall_type(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.QueryHallPlayerIdList)
 private:
  inline void set_has_hall_id();
  inline void clear_has_hall_id();
  inline void set_has_hall_type();
  inline void clear_has_hall_type();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 hall_id_;
  ::google::protobuf::int32 hall_type_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_QueryHallPlayerIdList_2eproto();
  friend void protobuf_AssignDesc_QueryHallPlayerIdList_2eproto();
  friend void protobuf_ShutdownFile_QueryHallPlayerIdList_2eproto();
  
  void InitAsDefaultInstance();
  static QueryHallPlayerIdList* default_instance_;
};
// ===================================================================


// ===================================================================

// QueryHallPlayerIdList

// required int32 hall_id = 1;
inline bool QueryHallPlayerIdList::has_hall_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void QueryHallPlayerIdList::set_has_hall_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void QueryHallPlayerIdList::clear_has_hall_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void QueryHallPlayerIdList::clear_hall_id() {
  hall_id_ = 0;
  clear_has_hall_id();
}
inline ::google::protobuf::int32 QueryHallPlayerIdList::hall_id() const {
  return hall_id_;
}
inline void QueryHallPlayerIdList::set_hall_id(::google::protobuf::int32 value) {
  set_has_hall_id();
  hall_id_ = value;
}

// optional int32 hall_type = 2;
inline bool QueryHallPlayerIdList::has_hall_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void QueryHallPlayerIdList::set_has_hall_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void QueryHallPlayerIdList::clear_has_hall_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void QueryHallPlayerIdList::clear_hall_type() {
  hall_type_ = 0;
  clear_has_hall_type();
}
inline ::google::protobuf::int32 QueryHallPlayerIdList::hall_type() const {
  return hall_type_;
}
inline void QueryHallPlayerIdList::set_hall_type(::google::protobuf::int32 value) {
  set_has_hall_type();
  hall_type_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::QueryHallPlayerIdList_traits>() {
  return ::game_connection::QueryHallPlayerIdList_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_QueryHallPlayerIdList_2eproto__INCLUDED
