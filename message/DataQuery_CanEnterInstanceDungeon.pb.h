// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataQuery_CanEnterInstanceDungeon.proto

#ifndef PROTOBUF_DataQuery_5fCanEnterInstanceDungeon_2eproto__INCLUDED
#define PROTOBUF_DataQuery_5fCanEnterInstanceDungeon_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataQuery_5fCanEnterInstanceDungeon_2eproto();
void protobuf_AssignDesc_DataQuery_5fCanEnterInstanceDungeon_2eproto();
void protobuf_ShutdownFile_DataQuery_5fCanEnterInstanceDungeon_2eproto();

class DataQuery_CanEnterInstanceDungeon;

enum DataQuery_CanEnterInstanceDungeon_traits {
  DataQuery_CanEnterInstanceDungeon_traits_value = 7103
};
bool DataQuery_CanEnterInstanceDungeon_traits_IsValid(int value);
const DataQuery_CanEnterInstanceDungeon_traits DataQuery_CanEnterInstanceDungeon_traits_traits_MIN = DataQuery_CanEnterInstanceDungeon_traits_value;
const DataQuery_CanEnterInstanceDungeon_traits DataQuery_CanEnterInstanceDungeon_traits_traits_MAX = DataQuery_CanEnterInstanceDungeon_traits_value;
const int DataQuery_CanEnterInstanceDungeon_traits_traits_ARRAYSIZE = DataQuery_CanEnterInstanceDungeon_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* DataQuery_CanEnterInstanceDungeon_traits_descriptor();
inline const ::std::string& DataQuery_CanEnterInstanceDungeon_traits_Name(DataQuery_CanEnterInstanceDungeon_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    DataQuery_CanEnterInstanceDungeon_traits_descriptor(), value);
}
inline bool DataQuery_CanEnterInstanceDungeon_traits_Parse(
    const ::std::string& name, DataQuery_CanEnterInstanceDungeon_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DataQuery_CanEnterInstanceDungeon_traits>(
    DataQuery_CanEnterInstanceDungeon_traits_descriptor(), name, value);
}
// ===================================================================

class DataQuery_CanEnterInstanceDungeon : public ::google::protobuf::Message {
 public:
  DataQuery_CanEnterInstanceDungeon();
  virtual ~DataQuery_CanEnterInstanceDungeon();
  
  DataQuery_CanEnterInstanceDungeon(const DataQuery_CanEnterInstanceDungeon& from);
  
  inline DataQuery_CanEnterInstanceDungeon& operator=(const DataQuery_CanEnterInstanceDungeon& from) {
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
  static const DataQuery_CanEnterInstanceDungeon& default_instance();
  
  void Swap(DataQuery_CanEnterInstanceDungeon* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_CanEnterInstanceDungeon* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_CanEnterInstanceDungeon& from);
  void MergeFrom(const DataQuery_CanEnterInstanceDungeon& from);
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
  
  typedef DataQuery_CanEnterInstanceDungeon_traits traits;
  static const traits value = DataQuery_CanEnterInstanceDungeon_traits_value;
  static inline bool traits_IsValid(int value) {
    return DataQuery_CanEnterInstanceDungeon_traits_IsValid(value);
  }
  static const traits traits_MIN =
    DataQuery_CanEnterInstanceDungeon_traits_traits_MIN;
  static const traits traits_MAX =
    DataQuery_CanEnterInstanceDungeon_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    DataQuery_CanEnterInstanceDungeon_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return DataQuery_CanEnterInstanceDungeon_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return DataQuery_CanEnterInstanceDungeon_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return DataQuery_CanEnterInstanceDungeon_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline ::google::protobuf::int32 key() const;
  inline void set_key(::google::protobuf::int32 value);
  
  // required bool ok = 2;
  inline bool has_ok() const;
  inline void clear_ok();
  static const int kOkFieldNumber = 2;
  inline bool ok() const;
  inline void set_ok(bool value);
  
  // optional int32 map_id = 3;
  inline bool has_map_id() const;
  inline void clear_map_id();
  static const int kMapIdFieldNumber = 3;
  inline ::google::protobuf::int32 map_id() const;
  inline void set_map_id(::google::protobuf::int32 value);
  
  // optional int32 level = 4;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 4;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_CanEnterInstanceDungeon)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_ok();
  inline void clear_has_ok();
  inline void set_has_map_id();
  inline void clear_has_map_id();
  inline void set_has_level();
  inline void clear_has_level();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 key_;
  bool ok_;
  ::google::protobuf::int32 map_id_;
  ::google::protobuf::int32 level_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fCanEnterInstanceDungeon_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fCanEnterInstanceDungeon_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fCanEnterInstanceDungeon_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_CanEnterInstanceDungeon* default_instance_;
};
// ===================================================================


// ===================================================================

// DataQuery_CanEnterInstanceDungeon

// required int32 key = 1;
inline bool DataQuery_CanEnterInstanceDungeon::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataQuery_CanEnterInstanceDungeon::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_key() {
  key_ = 0;
  clear_has_key();
}
inline ::google::protobuf::int32 DataQuery_CanEnterInstanceDungeon::key() const {
  return key_;
}
inline void DataQuery_CanEnterInstanceDungeon::set_key(::google::protobuf::int32 value) {
  set_has_key();
  key_ = value;
}

// required bool ok = 2;
inline bool DataQuery_CanEnterInstanceDungeon::has_ok() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataQuery_CanEnterInstanceDungeon::set_has_ok() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_has_ok() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_ok() {
  ok_ = false;
  clear_has_ok();
}
inline bool DataQuery_CanEnterInstanceDungeon::ok() const {
  return ok_;
}
inline void DataQuery_CanEnterInstanceDungeon::set_ok(bool value) {
  set_has_ok();
  ok_ = value;
}

// optional int32 map_id = 3;
inline bool DataQuery_CanEnterInstanceDungeon::has_map_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DataQuery_CanEnterInstanceDungeon::set_has_map_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_has_map_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_map_id() {
  map_id_ = 0;
  clear_has_map_id();
}
inline ::google::protobuf::int32 DataQuery_CanEnterInstanceDungeon::map_id() const {
  return map_id_;
}
inline void DataQuery_CanEnterInstanceDungeon::set_map_id(::google::protobuf::int32 value) {
  set_has_map_id();
  map_id_ = value;
}

// optional int32 level = 4;
inline bool DataQuery_CanEnterInstanceDungeon::has_level() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DataQuery_CanEnterInstanceDungeon::set_has_level() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_has_level() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DataQuery_CanEnterInstanceDungeon::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 DataQuery_CanEnterInstanceDungeon::level() const {
  return level_;
}
inline void DataQuery_CanEnterInstanceDungeon::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::DataQuery_CanEnterInstanceDungeon_traits>() {
  return ::game_connection::DataQuery_CanEnterInstanceDungeon_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataQuery_5fCanEnterInstanceDungeon_2eproto__INCLUDED
