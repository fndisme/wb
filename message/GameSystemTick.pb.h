// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameSystemTick.proto

#ifndef PROTOBUF_GameSystemTick_2eproto__INCLUDED
#define PROTOBUF_GameSystemTick_2eproto__INCLUDED

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
void  protobuf_AddDesc_GameSystemTick_2eproto();
void protobuf_AssignDesc_GameSystemTick_2eproto();
void protobuf_ShutdownFile_GameSystemTick_2eproto();

class GameSystemTick;

enum GameSystemTick_traits {
  GameSystemTick_traits_value = 3215
};
bool GameSystemTick_traits_IsValid(int value);
const GameSystemTick_traits GameSystemTick_traits_traits_MIN = GameSystemTick_traits_value;
const GameSystemTick_traits GameSystemTick_traits_traits_MAX = GameSystemTick_traits_value;
const int GameSystemTick_traits_traits_ARRAYSIZE = GameSystemTick_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* GameSystemTick_traits_descriptor();
inline const ::std::string& GameSystemTick_traits_Name(GameSystemTick_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    GameSystemTick_traits_descriptor(), value);
}
inline bool GameSystemTick_traits_Parse(
    const ::std::string& name, GameSystemTick_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<GameSystemTick_traits>(
    GameSystemTick_traits_descriptor(), name, value);
}
// ===================================================================

class GameSystemTick : public ::google::protobuf::Message {
 public:
  GameSystemTick();
  virtual ~GameSystemTick();
  
  GameSystemTick(const GameSystemTick& from);
  
  inline GameSystemTick& operator=(const GameSystemTick& from) {
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
  static const GameSystemTick& default_instance();
  
  void Swap(GameSystemTick* other);
  
  // implements Message ----------------------------------------------
  
  GameSystemTick* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GameSystemTick& from);
  void MergeFrom(const GameSystemTick& from);
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
  
  typedef GameSystemTick_traits traits;
  static const traits value = GameSystemTick_traits_value;
  static inline bool traits_IsValid(int value) {
    return GameSystemTick_traits_IsValid(value);
  }
  static const traits traits_MIN =
    GameSystemTick_traits_traits_MIN;
  static const traits traits_MAX =
    GameSystemTick_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    GameSystemTick_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return GameSystemTick_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return GameSystemTick_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return GameSystemTick_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int64 tick = 1;
  inline bool has_tick() const;
  inline void clear_tick();
  static const int kTickFieldNumber = 1;
  inline ::google::protobuf::int64 tick() const;
  inline void set_tick(::google::protobuf::int64 value);
  
  // optional int64 time = 2;
  inline bool has_time() const;
  inline void clear_time();
  static const int kTimeFieldNumber = 2;
  inline ::google::protobuf::int64 time() const;
  inline void set_time(::google::protobuf::int64 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.GameSystemTick)
 private:
  inline void set_has_tick();
  inline void clear_has_tick();
  inline void set_has_time();
  inline void clear_has_time();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int64 tick_;
  ::google::protobuf::int64 time_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_GameSystemTick_2eproto();
  friend void protobuf_AssignDesc_GameSystemTick_2eproto();
  friend void protobuf_ShutdownFile_GameSystemTick_2eproto();
  
  void InitAsDefaultInstance();
  static GameSystemTick* default_instance_;
};
// ===================================================================


// ===================================================================

// GameSystemTick

// required int64 tick = 1;
inline bool GameSystemTick::has_tick() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GameSystemTick::set_has_tick() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GameSystemTick::clear_has_tick() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GameSystemTick::clear_tick() {
  tick_ = GOOGLE_LONGLONG(0);
  clear_has_tick();
}
inline ::google::protobuf::int64 GameSystemTick::tick() const {
  return tick_;
}
inline void GameSystemTick::set_tick(::google::protobuf::int64 value) {
  set_has_tick();
  tick_ = value;
}

// optional int64 time = 2;
inline bool GameSystemTick::has_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GameSystemTick::set_has_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void GameSystemTick::clear_has_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void GameSystemTick::clear_time() {
  time_ = GOOGLE_LONGLONG(0);
  clear_has_time();
}
inline ::google::protobuf::int64 GameSystemTick::time() const {
  return time_;
}
inline void GameSystemTick::set_time(::google::protobuf::int64 value) {
  set_has_time();
  time_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::GameSystemTick_traits>() {
  return ::game_connection::GameSystemTick_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GameSystemTick_2eproto__INCLUDED
