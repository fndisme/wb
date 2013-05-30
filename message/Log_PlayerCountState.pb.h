// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Log_PlayerCountState.proto

#ifndef PROTOBUF_Log_5fPlayerCountState_2eproto__INCLUDED
#define PROTOBUF_Log_5fPlayerCountState_2eproto__INCLUDED

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
void  protobuf_AddDesc_Log_5fPlayerCountState_2eproto();
void protobuf_AssignDesc_Log_5fPlayerCountState_2eproto();
void protobuf_ShutdownFile_Log_5fPlayerCountState_2eproto();

class Log_PlayerCountState;

enum Log_PlayerCountState_traits {
  Log_PlayerCountState_traits_value = 12000
};
bool Log_PlayerCountState_traits_IsValid(int value);
const Log_PlayerCountState_traits Log_PlayerCountState_traits_traits_MIN = Log_PlayerCountState_traits_value;
const Log_PlayerCountState_traits Log_PlayerCountState_traits_traits_MAX = Log_PlayerCountState_traits_value;
const int Log_PlayerCountState_traits_traits_ARRAYSIZE = Log_PlayerCountState_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* Log_PlayerCountState_traits_descriptor();
inline const ::std::string& Log_PlayerCountState_traits_Name(Log_PlayerCountState_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    Log_PlayerCountState_traits_descriptor(), value);
}
inline bool Log_PlayerCountState_traits_Parse(
    const ::std::string& name, Log_PlayerCountState_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Log_PlayerCountState_traits>(
    Log_PlayerCountState_traits_descriptor(), name, value);
}
// ===================================================================

class Log_PlayerCountState : public ::google::protobuf::Message {
 public:
  Log_PlayerCountState();
  virtual ~Log_PlayerCountState();
  
  Log_PlayerCountState(const Log_PlayerCountState& from);
  
  inline Log_PlayerCountState& operator=(const Log_PlayerCountState& from) {
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
  static const Log_PlayerCountState& default_instance();
  
  void Swap(Log_PlayerCountState* other);
  
  // implements Message ----------------------------------------------
  
  Log_PlayerCountState* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Log_PlayerCountState& from);
  void MergeFrom(const Log_PlayerCountState& from);
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
  
  typedef Log_PlayerCountState_traits traits;
  static const traits value = Log_PlayerCountState_traits_value;
  static inline bool traits_IsValid(int value) {
    return Log_PlayerCountState_traits_IsValid(value);
  }
  static const traits traits_MIN =
    Log_PlayerCountState_traits_traits_MIN;
  static const traits traits_MAX =
    Log_PlayerCountState_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    Log_PlayerCountState_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return Log_PlayerCountState_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return Log_PlayerCountState_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return Log_PlayerCountState_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 current_player_number = 1;
  inline bool has_current_player_number() const;
  inline void clear_current_player_number();
  static const int kCurrentPlayerNumberFieldNumber = 1;
  inline ::google::protobuf::int32 current_player_number() const;
  inline void set_current_player_number(::google::protobuf::int32 value);
  
  // required int32 added_new_player_number = 2;
  inline bool has_added_new_player_number() const;
  inline void clear_added_new_player_number();
  static const int kAddedNewPlayerNumberFieldNumber = 2;
  inline ::google::protobuf::int32 added_new_player_number() const;
  inline void set_added_new_player_number(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.Log_PlayerCountState)
 private:
  inline void set_has_current_player_number();
  inline void clear_has_current_player_number();
  inline void set_has_added_new_player_number();
  inline void clear_has_added_new_player_number();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 current_player_number_;
  ::google::protobuf::int32 added_new_player_number_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_Log_5fPlayerCountState_2eproto();
  friend void protobuf_AssignDesc_Log_5fPlayerCountState_2eproto();
  friend void protobuf_ShutdownFile_Log_5fPlayerCountState_2eproto();
  
  void InitAsDefaultInstance();
  static Log_PlayerCountState* default_instance_;
};
// ===================================================================


// ===================================================================

// Log_PlayerCountState

// required int32 current_player_number = 1;
inline bool Log_PlayerCountState::has_current_player_number() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Log_PlayerCountState::set_has_current_player_number() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Log_PlayerCountState::clear_has_current_player_number() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Log_PlayerCountState::clear_current_player_number() {
  current_player_number_ = 0;
  clear_has_current_player_number();
}
inline ::google::protobuf::int32 Log_PlayerCountState::current_player_number() const {
  return current_player_number_;
}
inline void Log_PlayerCountState::set_current_player_number(::google::protobuf::int32 value) {
  set_has_current_player_number();
  current_player_number_ = value;
}

// required int32 added_new_player_number = 2;
inline bool Log_PlayerCountState::has_added_new_player_number() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Log_PlayerCountState::set_has_added_new_player_number() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Log_PlayerCountState::clear_has_added_new_player_number() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Log_PlayerCountState::clear_added_new_player_number() {
  added_new_player_number_ = 0;
  clear_has_added_new_player_number();
}
inline ::google::protobuf::int32 Log_PlayerCountState::added_new_player_number() const {
  return added_new_player_number_;
}
inline void Log_PlayerCountState::set_added_new_player_number(::google::protobuf::int32 value) {
  set_has_added_new_player_number();
  added_new_player_number_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::Log_PlayerCountState_traits>() {
  return ::game_connection::Log_PlayerCountState_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Log_5fPlayerCountState_2eproto__INCLUDED
