// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataQuery_Q_UseMoneyPoint.proto

#ifndef PROTOBUF_DataQuery_5fQ_5fUseMoneyPoint_2eproto__INCLUDED
#define PROTOBUF_DataQuery_5fQ_5fUseMoneyPoint_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataQuery_5fQ_5fUseMoneyPoint_2eproto();
void protobuf_AssignDesc_DataQuery_5fQ_5fUseMoneyPoint_2eproto();
void protobuf_ShutdownFile_DataQuery_5fQ_5fUseMoneyPoint_2eproto();

class DataQuery_Q_UseMoneyPoint;

enum DataQuery_Q_UseMoneyPoint_traits {
  DataQuery_Q_UseMoneyPoint_traits_value = 7086
};
bool DataQuery_Q_UseMoneyPoint_traits_IsValid(int value);
const DataQuery_Q_UseMoneyPoint_traits DataQuery_Q_UseMoneyPoint_traits_traits_MIN = DataQuery_Q_UseMoneyPoint_traits_value;
const DataQuery_Q_UseMoneyPoint_traits DataQuery_Q_UseMoneyPoint_traits_traits_MAX = DataQuery_Q_UseMoneyPoint_traits_value;
const int DataQuery_Q_UseMoneyPoint_traits_traits_ARRAYSIZE = DataQuery_Q_UseMoneyPoint_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* DataQuery_Q_UseMoneyPoint_traits_descriptor();
inline const ::std::string& DataQuery_Q_UseMoneyPoint_traits_Name(DataQuery_Q_UseMoneyPoint_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    DataQuery_Q_UseMoneyPoint_traits_descriptor(), value);
}
inline bool DataQuery_Q_UseMoneyPoint_traits_Parse(
    const ::std::string& name, DataQuery_Q_UseMoneyPoint_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DataQuery_Q_UseMoneyPoint_traits>(
    DataQuery_Q_UseMoneyPoint_traits_descriptor(), name, value);
}
// ===================================================================

class DataQuery_Q_UseMoneyPoint : public ::google::protobuf::Message {
 public:
  DataQuery_Q_UseMoneyPoint();
  virtual ~DataQuery_Q_UseMoneyPoint();
  
  DataQuery_Q_UseMoneyPoint(const DataQuery_Q_UseMoneyPoint& from);
  
  inline DataQuery_Q_UseMoneyPoint& operator=(const DataQuery_Q_UseMoneyPoint& from) {
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
  static const DataQuery_Q_UseMoneyPoint& default_instance();
  
  void Swap(DataQuery_Q_UseMoneyPoint* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_Q_UseMoneyPoint* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_Q_UseMoneyPoint& from);
  void MergeFrom(const DataQuery_Q_UseMoneyPoint& from);
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
  
  typedef DataQuery_Q_UseMoneyPoint_traits traits;
  static const traits value = DataQuery_Q_UseMoneyPoint_traits_value;
  static inline bool traits_IsValid(int value) {
    return DataQuery_Q_UseMoneyPoint_traits_IsValid(value);
  }
  static const traits traits_MIN =
    DataQuery_Q_UseMoneyPoint_traits_traits_MIN;
  static const traits traits_MAX =
    DataQuery_Q_UseMoneyPoint_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    DataQuery_Q_UseMoneyPoint_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return DataQuery_Q_UseMoneyPoint_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return DataQuery_Q_UseMoneyPoint_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return DataQuery_Q_UseMoneyPoint_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);
  
  // required int32 money = 2;
  inline bool has_money() const;
  inline void clear_money();
  static const int kMoneyFieldNumber = 2;
  inline ::google::protobuf::int32 money() const;
  inline void set_money(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_Q_UseMoneyPoint)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();
  inline void set_has_money();
  inline void clear_has_money();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 player_id_;
  ::google::protobuf::int32 money_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fQ_5fUseMoneyPoint_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fQ_5fUseMoneyPoint_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fQ_5fUseMoneyPoint_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_Q_UseMoneyPoint* default_instance_;
};
// ===================================================================


// ===================================================================

// DataQuery_Q_UseMoneyPoint

// required int32 player_id = 1;
inline bool DataQuery_Q_UseMoneyPoint::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataQuery_Q_UseMoneyPoint::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataQuery_Q_UseMoneyPoint::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataQuery_Q_UseMoneyPoint::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 DataQuery_Q_UseMoneyPoint::player_id() const {
  return player_id_;
}
inline void DataQuery_Q_UseMoneyPoint::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}

// required int32 money = 2;
inline bool DataQuery_Q_UseMoneyPoint::has_money() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataQuery_Q_UseMoneyPoint::set_has_money() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataQuery_Q_UseMoneyPoint::clear_has_money() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataQuery_Q_UseMoneyPoint::clear_money() {
  money_ = 0;
  clear_has_money();
}
inline ::google::protobuf::int32 DataQuery_Q_UseMoneyPoint::money() const {
  return money_;
}
inline void DataQuery_Q_UseMoneyPoint::set_money(::google::protobuf::int32 value) {
  set_has_money();
  money_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::DataQuery_Q_UseMoneyPoint_traits>() {
  return ::game_connection::DataQuery_Q_UseMoneyPoint_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataQuery_5fQ_5fUseMoneyPoint_2eproto__INCLUDED
