// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PlayerIdList.proto

#ifndef PROTOBUF_PlayerIdList_2eproto__INCLUDED
#define PROTOBUF_PlayerIdList_2eproto__INCLUDED

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
void  protobuf_AddDesc_PlayerIdList_2eproto();
void protobuf_AssignDesc_PlayerIdList_2eproto();
void protobuf_ShutdownFile_PlayerIdList_2eproto();

class PlayerIdList;
class PlayerIdList_PlayerInfomation;

enum PlayerIdList_traits {
  PlayerIdList_traits_value = 3021
};
bool PlayerIdList_traits_IsValid(int value);
const PlayerIdList_traits PlayerIdList_traits_traits_MIN = PlayerIdList_traits_value;
const PlayerIdList_traits PlayerIdList_traits_traits_MAX = PlayerIdList_traits_value;
const int PlayerIdList_traits_traits_ARRAYSIZE = PlayerIdList_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* PlayerIdList_traits_descriptor();
inline const ::std::string& PlayerIdList_traits_Name(PlayerIdList_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    PlayerIdList_traits_descriptor(), value);
}
inline bool PlayerIdList_traits_Parse(
    const ::std::string& name, PlayerIdList_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PlayerIdList_traits>(
    PlayerIdList_traits_descriptor(), name, value);
}
// ===================================================================

class PlayerIdList_PlayerInfomation : public ::google::protobuf::Message {
 public:
  PlayerIdList_PlayerInfomation();
  virtual ~PlayerIdList_PlayerInfomation();
  
  PlayerIdList_PlayerInfomation(const PlayerIdList_PlayerInfomation& from);
  
  inline PlayerIdList_PlayerInfomation& operator=(const PlayerIdList_PlayerInfomation& from) {
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
  static const PlayerIdList_PlayerInfomation& default_instance();
  
  void Swap(PlayerIdList_PlayerInfomation* other);
  
  // implements Message ----------------------------------------------
  
  PlayerIdList_PlayerInfomation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayerIdList_PlayerInfomation& from);
  void MergeFrom(const PlayerIdList_PlayerInfomation& from);
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
  
  // accessors -------------------------------------------------------
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // required bytes name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const void* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required int32 level = 3;
  inline bool has_level() const;
  inline void clear_level();
  static const int kLevelFieldNumber = 3;
  inline ::google::protobuf::int32 level() const;
  inline void set_level(::google::protobuf::int32 value);
  
  // required int32 photo = 4;
  inline bool has_photo() const;
  inline void clear_photo();
  static const int kPhotoFieldNumber = 4;
  inline ::google::protobuf::int32 photo() const;
  inline void set_photo(::google::protobuf::int32 value);
  
  // required int32 nation = 5;
  inline bool has_nation() const;
  inline void clear_nation();
  static const int kNationFieldNumber = 5;
  inline ::google::protobuf::int32 nation() const;
  inline void set_nation(::google::protobuf::int32 value);
  
  // required int32 league = 6;
  inline bool has_league() const;
  inline void clear_league();
  static const int kLeagueFieldNumber = 6;
  inline ::google::protobuf::int32 league() const;
  inline void set_league(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.PlayerIdList.PlayerInfomation)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_level();
  inline void clear_has_level();
  inline void set_has_photo();
  inline void clear_has_photo();
  inline void set_has_nation();
  inline void clear_has_nation();
  inline void set_has_league();
  inline void clear_has_league();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 level_;
  ::google::protobuf::int32 photo_;
  ::google::protobuf::int32 nation_;
  ::google::protobuf::int32 league_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];
  
  friend void  protobuf_AddDesc_PlayerIdList_2eproto();
  friend void protobuf_AssignDesc_PlayerIdList_2eproto();
  friend void protobuf_ShutdownFile_PlayerIdList_2eproto();
  
  void InitAsDefaultInstance();
  static PlayerIdList_PlayerInfomation* default_instance_;
};
// -------------------------------------------------------------------

class PlayerIdList : public ::google::protobuf::Message {
 public:
  PlayerIdList();
  virtual ~PlayerIdList();
  
  PlayerIdList(const PlayerIdList& from);
  
  inline PlayerIdList& operator=(const PlayerIdList& from) {
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
  static const PlayerIdList& default_instance();
  
  void Swap(PlayerIdList* other);
  
  // implements Message ----------------------------------------------
  
  PlayerIdList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PlayerIdList& from);
  void MergeFrom(const PlayerIdList& from);
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
  
  typedef PlayerIdList_PlayerInfomation PlayerInfomation;
  
  typedef PlayerIdList_traits traits;
  static const traits value = PlayerIdList_traits_value;
  static inline bool traits_IsValid(int value) {
    return PlayerIdList_traits_IsValid(value);
  }
  static const traits traits_MIN =
    PlayerIdList_traits_traits_MIN;
  static const traits traits_MAX =
    PlayerIdList_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    PlayerIdList_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return PlayerIdList_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return PlayerIdList_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return PlayerIdList_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.PlayerIdList.PlayerInfomation player = 1;
  inline int player_size() const;
  inline void clear_player();
  static const int kPlayerFieldNumber = 1;
  inline const ::game_connection::PlayerIdList_PlayerInfomation& player(int index) const;
  inline ::game_connection::PlayerIdList_PlayerInfomation* mutable_player(int index);
  inline ::game_connection::PlayerIdList_PlayerInfomation* add_player();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::PlayerIdList_PlayerInfomation >&
      player() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::PlayerIdList_PlayerInfomation >*
      mutable_player();
  
  // required int32 dummy = 2;
  inline bool has_dummy() const;
  inline void clear_dummy();
  static const int kDummyFieldNumber = 2;
  inline ::google::protobuf::int32 dummy() const;
  inline void set_dummy(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.PlayerIdList)
 private:
  inline void set_has_dummy();
  inline void clear_has_dummy();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::PlayerIdList_PlayerInfomation > player_;
  ::google::protobuf::int32 dummy_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_PlayerIdList_2eproto();
  friend void protobuf_AssignDesc_PlayerIdList_2eproto();
  friend void protobuf_ShutdownFile_PlayerIdList_2eproto();
  
  void InitAsDefaultInstance();
  static PlayerIdList* default_instance_;
};
// ===================================================================


// ===================================================================

// PlayerIdList_PlayerInfomation

// required int32 id = 1;
inline bool PlayerIdList_PlayerInfomation::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PlayerIdList_PlayerInfomation::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 PlayerIdList_PlayerInfomation::id() const {
  return id_;
}
inline void PlayerIdList_PlayerInfomation::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required bytes name = 2;
inline bool PlayerIdList_PlayerInfomation::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PlayerIdList_PlayerInfomation::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& PlayerIdList_PlayerInfomation::name() const {
  return *name_;
}
inline void PlayerIdList_PlayerInfomation::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void PlayerIdList_PlayerInfomation::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void PlayerIdList_PlayerInfomation::set_name(const void* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PlayerIdList_PlayerInfomation::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* PlayerIdList_PlayerInfomation::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 level = 3;
inline bool PlayerIdList_PlayerInfomation::has_level() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_level() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_level() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PlayerIdList_PlayerInfomation::clear_level() {
  level_ = 0;
  clear_has_level();
}
inline ::google::protobuf::int32 PlayerIdList_PlayerInfomation::level() const {
  return level_;
}
inline void PlayerIdList_PlayerInfomation::set_level(::google::protobuf::int32 value) {
  set_has_level();
  level_ = value;
}

// required int32 photo = 4;
inline bool PlayerIdList_PlayerInfomation::has_photo() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_photo() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_photo() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PlayerIdList_PlayerInfomation::clear_photo() {
  photo_ = 0;
  clear_has_photo();
}
inline ::google::protobuf::int32 PlayerIdList_PlayerInfomation::photo() const {
  return photo_;
}
inline void PlayerIdList_PlayerInfomation::set_photo(::google::protobuf::int32 value) {
  set_has_photo();
  photo_ = value;
}

// required int32 nation = 5;
inline bool PlayerIdList_PlayerInfomation::has_nation() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_nation() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_nation() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PlayerIdList_PlayerInfomation::clear_nation() {
  nation_ = 0;
  clear_has_nation();
}
inline ::google::protobuf::int32 PlayerIdList_PlayerInfomation::nation() const {
  return nation_;
}
inline void PlayerIdList_PlayerInfomation::set_nation(::google::protobuf::int32 value) {
  set_has_nation();
  nation_ = value;
}

// required int32 league = 6;
inline bool PlayerIdList_PlayerInfomation::has_league() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void PlayerIdList_PlayerInfomation::set_has_league() {
  _has_bits_[0] |= 0x00000020u;
}
inline void PlayerIdList_PlayerInfomation::clear_has_league() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void PlayerIdList_PlayerInfomation::clear_league() {
  league_ = 0;
  clear_has_league();
}
inline ::google::protobuf::int32 PlayerIdList_PlayerInfomation::league() const {
  return league_;
}
inline void PlayerIdList_PlayerInfomation::set_league(::google::protobuf::int32 value) {
  set_has_league();
  league_ = value;
}

// -------------------------------------------------------------------

// PlayerIdList

// repeated .game_connection.PlayerIdList.PlayerInfomation player = 1;
inline int PlayerIdList::player_size() const {
  return player_.size();
}
inline void PlayerIdList::clear_player() {
  player_.Clear();
}
inline const ::game_connection::PlayerIdList_PlayerInfomation& PlayerIdList::player(int index) const {
  return player_.Get(index);
}
inline ::game_connection::PlayerIdList_PlayerInfomation* PlayerIdList::mutable_player(int index) {
  return player_.Mutable(index);
}
inline ::game_connection::PlayerIdList_PlayerInfomation* PlayerIdList::add_player() {
  return player_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::PlayerIdList_PlayerInfomation >&
PlayerIdList::player() const {
  return player_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::PlayerIdList_PlayerInfomation >*
PlayerIdList::mutable_player() {
  return &player_;
}

// required int32 dummy = 2;
inline bool PlayerIdList::has_dummy() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PlayerIdList::set_has_dummy() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PlayerIdList::clear_has_dummy() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PlayerIdList::clear_dummy() {
  dummy_ = 0;
  clear_has_dummy();
}
inline ::google::protobuf::int32 PlayerIdList::dummy() const {
  return dummy_;
}
inline void PlayerIdList::set_dummy(::google::protobuf::int32 value) {
  set_has_dummy();
  dummy_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::PlayerIdList_traits>() {
  return ::game_connection::PlayerIdList_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_PlayerIdList_2eproto__INCLUDED
