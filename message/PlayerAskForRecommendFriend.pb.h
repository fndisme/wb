// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PlayerAskForRecommendFriend.proto

#ifndef PROTOBUF_PlayerAskForRecommendFriend_2eproto__INCLUDED
#define PROTOBUF_PlayerAskForRecommendFriend_2eproto__INCLUDED

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
void  protobuf_AddDesc_PlayerAskForRecommendFriend_2eproto();
void protobuf_AssignDesc_PlayerAskForRecommendFriend_2eproto();
void protobuf_ShutdownFile_PlayerAskForRecommendFriend_2eproto();

class PlayerAskForRecommendFriend;

enum PlayerAskForRecommendFriend_traits {
  PlayerAskForRecommendFriend_traits_value = 3457
};
bool PlayerAskForRecommendFriend_traits_IsValid(int value);
const PlayerAskForRecommendFriend_traits PlayerAskForRecommendFriend_traits_traits_MIN = PlayerAskForRecommendFriend_traits_value;
const PlayerAskForRecommendFriend_traits PlayerAskForRecommendFriend_traits_traits_MAX = PlayerAskForRecommendFriend_traits_value;
const int PlayerAskForRecommendFriend_traits_traits_ARRAYSIZE = PlayerAskForRecommendFriend_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerAskForRecommendFriend_traits_descriptor();
inline const ::std::string& PlayerAskForRecommendFriend_traits_Name(PlayerAskForRecommendFriend_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerAskForRecommendFriend_traits_descriptor(), value);
}
inline bool PlayerAskForRecommendFriend_traits_Parse(
    const ::std::string& name, PlayerAskForRecommendFriend_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerAskForRecommendFriend_traits>(
    PlayerAskForRecommendFriend_traits_descriptor(), name, value);
}
enum PlayerAskForRecommendFriend_Limit {
  PlayerAskForRecommendFriend_Limit_PageSize = 18
};
bool PlayerAskForRecommendFriend_Limit_IsValid(int value);
const PlayerAskForRecommendFriend_Limit PlayerAskForRecommendFriend_Limit_Limit_MIN = PlayerAskForRecommendFriend_Limit_PageSize;
const PlayerAskForRecommendFriend_Limit PlayerAskForRecommendFriend_Limit_Limit_MAX = PlayerAskForRecommendFriend_Limit_PageSize;
const int PlayerAskForRecommendFriend_Limit_Limit_ARRAYSIZE = PlayerAskForRecommendFriend_Limit_Limit_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerAskForRecommendFriend_Limit_descriptor();
inline const ::std::string& PlayerAskForRecommendFriend_Limit_Name(PlayerAskForRecommendFriend_Limit value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerAskForRecommendFriend_Limit_descriptor(), value);
}
inline bool PlayerAskForRecommendFriend_Limit_Parse(
    const ::std::string& name, PlayerAskForRecommendFriend_Limit* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerAskForRecommendFriend_Limit>(
    PlayerAskForRecommendFriend_Limit_descriptor(), name, value);
}
// ===================================================================

class PlayerAskForRecommendFriend : public ::google::protobuf::Message {
 public:
  PlayerAskForRecommendFriend();
  virtual ~PlayerAskForRecommendFriend();
  
  PlayerAskForRecommendFriend(const PlayerAskForRecommendFriend& from);
  
  inline PlayerAskForRecommendFriend& operator=(const PlayerAskForRecommendFriend& from) {
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
  static const PlayerAskForRecommendFriend& default_instance();
  
  void Swap(PlayerAskForRecommendFriend* other);
  
  // implements Message ----------------------------------------------
  
  PlayerAskForRecommendFriend* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayerAskForRecommendFriend& from);
  void MergeFrom(const PlayerAskForRecommendFriend& from);
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
  
  typedef PlayerAskForRecommendFriend_traits traits;
  static const traits value = PlayerAskForRecommendFriend_traits_value;
  static inline bool traits_IsValid(int value) {
    return PlayerAskForRecommendFriend_traits_IsValid(value);
  }
  static const traits traits_MIN =
    PlayerAskForRecommendFriend_traits_traits_MIN;
  static const traits traits_MAX =
    PlayerAskForRecommendFriend_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    PlayerAskForRecommendFriend_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return PlayerAskForRecommendFriend_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return PlayerAskForRecommendFriend_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return PlayerAskForRecommendFriend_traits_Parse(name, value);
  }
  
  typedef PlayerAskForRecommendFriend_Limit Limit;
  static const Limit PageSize = PlayerAskForRecommendFriend_Limit_PageSize;
  static inline bool Limit_IsValid(int value) {
    return PlayerAskForRecommendFriend_Limit_IsValid(value);
  }
  static const Limit Limit_MIN =
    PlayerAskForRecommendFriend_Limit_Limit_MIN;
  static const Limit Limit_MAX =
    PlayerAskForRecommendFriend_Limit_Limit_MAX;
  static const int Limit_ARRAYSIZE =
    PlayerAskForRecommendFriend_Limit_Limit_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Limit_descriptor() {
    return PlayerAskForRecommendFriend_Limit_descriptor();
  }
  static inline const ::std::string& Limit_Name(Limit value) {
    return PlayerAskForRecommendFriend_Limit_Name(value);
  }
  static inline bool Limit_Parse(const ::std::string& name,
      Limit* value) {
    return PlayerAskForRecommendFriend_Limit_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // optional uint32 hint = 1;
  inline bool has_hint() const;
  inline void clear_hint();
  static const int kHintFieldNumber = 1;
  inline ::google::protobuf::uint32 hint() const;
  inline void set_hint(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.PlayerAskForRecommendFriend)
 private:
  inline void set_has_hint();
  inline void clear_has_hint();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 hint_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_PlayerAskForRecommendFriend_2eproto();
  friend void protobuf_AssignDesc_PlayerAskForRecommendFriend_2eproto();
  friend void protobuf_ShutdownFile_PlayerAskForRecommendFriend_2eproto();
  
  void InitAsDefaultInstance();
  static PlayerAskForRecommendFriend* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayerAskForRecommendFriend

// optional uint32 hint = 1;
inline bool PlayerAskForRecommendFriend::has_hint() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerAskForRecommendFriend::set_has_hint() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerAskForRecommendFriend::clear_has_hint() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerAskForRecommendFriend::clear_hint() {
  hint_ = 0u;
  clear_has_hint();
}
inline ::google::protobuf::uint32 PlayerAskForRecommendFriend::hint() const {
  return hint_;
}
inline void PlayerAskForRecommendFriend::set_hint(::google::protobuf::uint32 value) {
  set_has_hint();
  hint_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::PlayerAskForRecommendFriend_traits>() {
  return ::game_connection::PlayerAskForRecommendFriend_traits_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::PlayerAskForRecommendFriend_Limit>() {
  return ::game_connection::PlayerAskForRecommendFriend_Limit_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_PlayerAskForRecommendFriend_2eproto__INCLUDED
