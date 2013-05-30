// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataCall_RecordPlayerRoundFightResult.proto

#ifndef PROTOBUF_DataCall_5fRecordPlayerRoundFightResult_2eproto__INCLUDED
#define PROTOBUF_DataCall_5fRecordPlayerRoundFightResult_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataCall_5fRecordPlayerRoundFightResult_2eproto();
void protobuf_AssignDesc_DataCall_5fRecordPlayerRoundFightResult_2eproto();
void protobuf_ShutdownFile_DataCall_5fRecordPlayerRoundFightResult_2eproto();

class DataCall_RecordPlayerRoundFightResult;

enum DataCall_RecordPlayerRoundFightResult_traits {
  DataCall_RecordPlayerRoundFightResult_traits_value = 7013
};
bool DataCall_RecordPlayerRoundFightResult_traits_IsValid(int value);
const DataCall_RecordPlayerRoundFightResult_traits DataCall_RecordPlayerRoundFightResult_traits_traits_MIN = DataCall_RecordPlayerRoundFightResult_traits_value;
const DataCall_RecordPlayerRoundFightResult_traits DataCall_RecordPlayerRoundFightResult_traits_traits_MAX = DataCall_RecordPlayerRoundFightResult_traits_value;
const int DataCall_RecordPlayerRoundFightResult_traits_traits_ARRAYSIZE = DataCall_RecordPlayerRoundFightResult_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* DataCall_RecordPlayerRoundFightResult_traits_descriptor();
inline const ::std::string& DataCall_RecordPlayerRoundFightResult_traits_Name(DataCall_RecordPlayerRoundFightResult_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    DataCall_RecordPlayerRoundFightResult_traits_descriptor(), value);
}
inline bool DataCall_RecordPlayerRoundFightResult_traits_Parse(
    const ::std::string& name, DataCall_RecordPlayerRoundFightResult_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DataCall_RecordPlayerRoundFightResult_traits>(
    DataCall_RecordPlayerRoundFightResult_traits_descriptor(), name, value);
}
// ===================================================================

class DataCall_RecordPlayerRoundFightResult : public ::google::protobuf::Message {
 public:
  DataCall_RecordPlayerRoundFightResult();
  virtual ~DataCall_RecordPlayerRoundFightResult();
  
  DataCall_RecordPlayerRoundFightResult(const DataCall_RecordPlayerRoundFightResult& from);
  
  inline DataCall_RecordPlayerRoundFightResult& operator=(const DataCall_RecordPlayerRoundFightResult& from) {
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
  static const DataCall_RecordPlayerRoundFightResult& default_instance();
  
  void Swap(DataCall_RecordPlayerRoundFightResult* other);
  
  // implements Message ----------------------------------------------
  
  DataCall_RecordPlayerRoundFightResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataCall_RecordPlayerRoundFightResult& from);
  void MergeFrom(const DataCall_RecordPlayerRoundFightResult& from);
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
  
  typedef DataCall_RecordPlayerRoundFightResult_traits traits;
  static const traits value = DataCall_RecordPlayerRoundFightResult_traits_value;
  static inline bool traits_IsValid(int value) {
    return DataCall_RecordPlayerRoundFightResult_traits_IsValid(value);
  }
  static const traits traits_MIN =
    DataCall_RecordPlayerRoundFightResult_traits_traits_MIN;
  static const traits traits_MAX =
    DataCall_RecordPlayerRoundFightResult_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    DataCall_RecordPlayerRoundFightResult_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return DataCall_RecordPlayerRoundFightResult_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return DataCall_RecordPlayerRoundFightResult_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return DataCall_RecordPlayerRoundFightResult_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 pid = 1;
  inline bool has_pid() const;
  inline void clear_pid();
  static const int kPidFieldNumber = 1;
  inline ::google::protobuf::int32 pid() const;
  inline void set_pid(::google::protobuf::int32 value);
  
  // required bool is_winner = 2;
  inline bool has_is_winner() const;
  inline void clear_is_winner();
  static const int kIsWinnerFieldNumber = 2;
  inline bool is_winner() const;
  inline void set_is_winner(bool value);
  
  // required int32 map_id = 3;
  inline bool has_map_id() const;
  inline void clear_map_id();
  static const int kMapIdFieldNumber = 3;
  inline ::google::protobuf::int32 map_id() const;
  inline void set_map_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.DataCall_RecordPlayerRoundFightResult)
 private:
  inline void set_has_pid();
  inline void clear_has_pid();
  inline void set_has_is_winner();
  inline void clear_has_is_winner();
  inline void set_has_map_id();
  inline void clear_has_map_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 pid_;
  bool is_winner_;
  ::google::protobuf::int32 map_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataCall_5fRecordPlayerRoundFightResult_2eproto();
  friend void protobuf_AssignDesc_DataCall_5fRecordPlayerRoundFightResult_2eproto();
  friend void protobuf_ShutdownFile_DataCall_5fRecordPlayerRoundFightResult_2eproto();
  
  void InitAsDefaultInstance();
  static DataCall_RecordPlayerRoundFightResult* default_instance_;
};
// ===================================================================


// ===================================================================

// DataCall_RecordPlayerRoundFightResult

// required int32 pid = 1;
inline bool DataCall_RecordPlayerRoundFightResult::has_pid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataCall_RecordPlayerRoundFightResult::set_has_pid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_has_pid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_pid() {
  pid_ = 0;
  clear_has_pid();
}
inline ::google::protobuf::int32 DataCall_RecordPlayerRoundFightResult::pid() const {
  return pid_;
}
inline void DataCall_RecordPlayerRoundFightResult::set_pid(::google::protobuf::int32 value) {
  set_has_pid();
  pid_ = value;
}

// required bool is_winner = 2;
inline bool DataCall_RecordPlayerRoundFightResult::has_is_winner() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataCall_RecordPlayerRoundFightResult::set_has_is_winner() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_has_is_winner() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_is_winner() {
  is_winner_ = false;
  clear_has_is_winner();
}
inline bool DataCall_RecordPlayerRoundFightResult::is_winner() const {
  return is_winner_;
}
inline void DataCall_RecordPlayerRoundFightResult::set_is_winner(bool value) {
  set_has_is_winner();
  is_winner_ = value;
}

// required int32 map_id = 3;
inline bool DataCall_RecordPlayerRoundFightResult::has_map_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DataCall_RecordPlayerRoundFightResult::set_has_map_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_has_map_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DataCall_RecordPlayerRoundFightResult::clear_map_id() {
  map_id_ = 0;
  clear_has_map_id();
}
inline ::google::protobuf::int32 DataCall_RecordPlayerRoundFightResult::map_id() const {
  return map_id_;
}
inline void DataCall_RecordPlayerRoundFightResult::set_map_id(::google::protobuf::int32 value) {
  set_has_map_id();
  map_id_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::DataCall_RecordPlayerRoundFightResult_traits>() {
  return ::game_connection::DataCall_RecordPlayerRoundFightResult_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataCall_5fRecordPlayerRoundFightResult_2eproto__INCLUDED
