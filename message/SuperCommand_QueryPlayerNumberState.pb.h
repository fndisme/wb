// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SuperCommand_QueryPlayerNumberState.proto

#ifndef PROTOBUF_SuperCommand_5fQueryPlayerNumberState_2eproto__INCLUDED
#define PROTOBUF_SuperCommand_5fQueryPlayerNumberState_2eproto__INCLUDED

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
void  protobuf_AddDesc_SuperCommand_5fQueryPlayerNumberState_2eproto();
void protobuf_AssignDesc_SuperCommand_5fQueryPlayerNumberState_2eproto();
void protobuf_ShutdownFile_SuperCommand_5fQueryPlayerNumberState_2eproto();

class SuperCommand_QueryPlayerNumberState;

enum SuperCommand_QueryPlayerNumberState_traits {
  SuperCommand_QueryPlayerNumberState_traits_value = 10023
};
bool SuperCommand_QueryPlayerNumberState_traits_IsValid(int value);
const SuperCommand_QueryPlayerNumberState_traits SuperCommand_QueryPlayerNumberState_traits_traits_MIN = SuperCommand_QueryPlayerNumberState_traits_value;
const SuperCommand_QueryPlayerNumberState_traits SuperCommand_QueryPlayerNumberState_traits_traits_MAX = SuperCommand_QueryPlayerNumberState_traits_value;
const int SuperCommand_QueryPlayerNumberState_traits_traits_ARRAYSIZE = SuperCommand_QueryPlayerNumberState_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* SuperCommand_QueryPlayerNumberState_traits_descriptor();
inline const ::std::string& SuperCommand_QueryPlayerNumberState_traits_Name(SuperCommand_QueryPlayerNumberState_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    SuperCommand_QueryPlayerNumberState_traits_descriptor(), value);
}
inline bool SuperCommand_QueryPlayerNumberState_traits_Parse(
    const ::std::string& name, SuperCommand_QueryPlayerNumberState_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<SuperCommand_QueryPlayerNumberState_traits>(
    SuperCommand_QueryPlayerNumberState_traits_descriptor(), name, value);
}
// ===================================================================

class SuperCommand_QueryPlayerNumberState : public ::google::protobuf::Message {
 public:
  SuperCommand_QueryPlayerNumberState();
  virtual ~SuperCommand_QueryPlayerNumberState();
  
  SuperCommand_QueryPlayerNumberState(const SuperCommand_QueryPlayerNumberState& from);
  
  inline SuperCommand_QueryPlayerNumberState& operator=(const SuperCommand_QueryPlayerNumberState& from) {
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
  static const SuperCommand_QueryPlayerNumberState& default_instance();
  
  void Swap(SuperCommand_QueryPlayerNumberState* other);
  
  // implements Message ----------------------------------------------
  
  SuperCommand_QueryPlayerNumberState* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SuperCommand_QueryPlayerNumberState& from);
  void MergeFrom(const SuperCommand_QueryPlayerNumberState& from);
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
  
  typedef SuperCommand_QueryPlayerNumberState_traits traits;
  static const traits value = SuperCommand_QueryPlayerNumberState_traits_value;
  static inline bool traits_IsValid(int value) {
    return SuperCommand_QueryPlayerNumberState_traits_IsValid(value);
  }
  static const traits traits_MIN =
    SuperCommand_QueryPlayerNumberState_traits_traits_MIN;
  static const traits traits_MAX =
    SuperCommand_QueryPlayerNumberState_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    SuperCommand_QueryPlayerNumberState_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return SuperCommand_QueryPlayerNumberState_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return SuperCommand_QueryPlayerNumberState_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return SuperCommand_QueryPlayerNumberState_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.SuperCommand_QueryPlayerNumberState)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 player_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_SuperCommand_5fQueryPlayerNumberState_2eproto();
  friend void protobuf_AssignDesc_SuperCommand_5fQueryPlayerNumberState_2eproto();
  friend void protobuf_ShutdownFile_SuperCommand_5fQueryPlayerNumberState_2eproto();
  
  void InitAsDefaultInstance();
  static SuperCommand_QueryPlayerNumberState* default_instance_;
};
// ===================================================================


// ===================================================================

// SuperCommand_QueryPlayerNumberState

// required int32 player_id = 1;
inline bool SuperCommand_QueryPlayerNumberState::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SuperCommand_QueryPlayerNumberState::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SuperCommand_QueryPlayerNumberState::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SuperCommand_QueryPlayerNumberState::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 SuperCommand_QueryPlayerNumberState::player_id() const {
  return player_id_;
}
inline void SuperCommand_QueryPlayerNumberState::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::SuperCommand_QueryPlayerNumberState_traits>() {
  return ::game_connection::SuperCommand_QueryPlayerNumberState_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_SuperCommand_5fQueryPlayerNumberState_2eproto__INCLUDED
