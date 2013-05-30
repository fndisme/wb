// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityWhipRankAward.proto

#ifndef PROTOBUF_UnityWhipRankAward_2eproto__INCLUDED
#define PROTOBUF_UnityWhipRankAward_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityWhipRankAward_2eproto();
void protobuf_AssignDesc_UnityWhipRankAward_2eproto();
void protobuf_ShutdownFile_UnityWhipRankAward_2eproto();

class UnityWhipRankAward;
class UnityWhipRankAward_Reward;

enum UnityWhipRankAward_traits {
  UnityWhipRankAward_traits_value = 4321
};
bool UnityWhipRankAward_traits_IsValid(int value);
const UnityWhipRankAward_traits UnityWhipRankAward_traits_traits_MIN = UnityWhipRankAward_traits_value;
const UnityWhipRankAward_traits UnityWhipRankAward_traits_traits_MAX = UnityWhipRankAward_traits_value;
const int UnityWhipRankAward_traits_traits_ARRAYSIZE = UnityWhipRankAward_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityWhipRankAward_traits_descriptor();
inline const ::std::string& UnityWhipRankAward_traits_Name(UnityWhipRankAward_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityWhipRankAward_traits_descriptor(), value);
}
inline bool UnityWhipRankAward_traits_Parse(
    const ::std::string& name, UnityWhipRankAward_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityWhipRankAward_traits>(
    UnityWhipRankAward_traits_descriptor(), name, value);
}
enum UnityWhipRankAward_AwardType {
  UnityWhipRankAward_AwardType_GAT_NULL = 0,
  UnityWhipRankAward_AwardType_GAT_MONEY = 1,
  UnityWhipRankAward_AwardType_GAT_PROP_OR_EQUIPMENT = 2,
  UnityWhipRankAward_AwardType_GAT_SCORE = 3
};
bool UnityWhipRankAward_AwardType_IsValid(int value);
const UnityWhipRankAward_AwardType UnityWhipRankAward_AwardType_AwardType_MIN = UnityWhipRankAward_AwardType_GAT_NULL;
const UnityWhipRankAward_AwardType UnityWhipRankAward_AwardType_AwardType_MAX = UnityWhipRankAward_AwardType_GAT_SCORE;
const int UnityWhipRankAward_AwardType_AwardType_ARRAYSIZE = UnityWhipRankAward_AwardType_AwardType_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityWhipRankAward_AwardType_descriptor();
inline const ::std::string& UnityWhipRankAward_AwardType_Name(UnityWhipRankAward_AwardType value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityWhipRankAward_AwardType_descriptor(), value);
}
inline bool UnityWhipRankAward_AwardType_Parse(
    const ::std::string& name, UnityWhipRankAward_AwardType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityWhipRankAward_AwardType>(
    UnityWhipRankAward_AwardType_descriptor(), name, value);
}
// ===================================================================

class UnityWhipRankAward_Reward : public ::google::protobuf::Message {
 public:
  UnityWhipRankAward_Reward();
  virtual ~UnityWhipRankAward_Reward();
  
  UnityWhipRankAward_Reward(const UnityWhipRankAward_Reward& from);
  
  inline UnityWhipRankAward_Reward& operator=(const UnityWhipRankAward_Reward& from) {
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
  static const UnityWhipRankAward_Reward& default_instance();
  
  void Swap(UnityWhipRankAward_Reward* other);
  
  // implements Message ----------------------------------------------
  
  UnityWhipRankAward_Reward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityWhipRankAward_Reward& from);
  void MergeFrom(const UnityWhipRankAward_Reward& from);
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
  
  // required int32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);
  
  // required int32 object_id = 2;
  inline bool has_object_id() const;
  inline void clear_object_id();
  static const int kObjectIdFieldNumber = 2;
  inline ::google::protobuf::int32 object_id() const;
  inline void set_object_id(::google::protobuf::int32 value);
  
  // required int32 size = 3;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 3;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);
  
  // required int32 order = 4;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 4;
  inline ::google::protobuf::int32 order() const;
  inline void set_order(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityWhipRankAward.Reward)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_object_id();
  inline void clear_has_object_id();
  inline void set_has_size();
  inline void clear_has_size();
  inline void set_has_order();
  inline void clear_has_order();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 type_;
  ::google::protobuf::int32 object_id_;
  ::google::protobuf::int32 size_;
  ::google::protobuf::int32 order_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityWhipRankAward_2eproto();
  friend void protobuf_AssignDesc_UnityWhipRankAward_2eproto();
  friend void protobuf_ShutdownFile_UnityWhipRankAward_2eproto();
  
  void InitAsDefaultInstance();
  static UnityWhipRankAward_Reward* default_instance_;
};
// -------------------------------------------------------------------

class UnityWhipRankAward : public ::google::protobuf::Message {
 public:
  UnityWhipRankAward();
  virtual ~UnityWhipRankAward();
  
  UnityWhipRankAward(const UnityWhipRankAward& from);
  
  inline UnityWhipRankAward& operator=(const UnityWhipRankAward& from) {
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
  static const UnityWhipRankAward& default_instance();
  
  void Swap(UnityWhipRankAward* other);
  
  // implements Message ----------------------------------------------
  
  UnityWhipRankAward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityWhipRankAward& from);
  void MergeFrom(const UnityWhipRankAward& from);
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
  
  typedef UnityWhipRankAward_Reward Reward;
  
  typedef UnityWhipRankAward_traits traits;
  static const traits value = UnityWhipRankAward_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityWhipRankAward_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityWhipRankAward_traits_traits_MIN;
  static const traits traits_MAX =
    UnityWhipRankAward_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityWhipRankAward_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityWhipRankAward_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityWhipRankAward_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityWhipRankAward_traits_Parse(name, value);
  }
  
  typedef UnityWhipRankAward_AwardType AwardType;
  static const AwardType GAT_NULL = UnityWhipRankAward_AwardType_GAT_NULL;
  static const AwardType GAT_MONEY = UnityWhipRankAward_AwardType_GAT_MONEY;
  static const AwardType GAT_PROP_OR_EQUIPMENT = UnityWhipRankAward_AwardType_GAT_PROP_OR_EQUIPMENT;
  static const AwardType GAT_SCORE = UnityWhipRankAward_AwardType_GAT_SCORE;
  static inline bool AwardType_IsValid(int value) {
    return UnityWhipRankAward_AwardType_IsValid(value);
  }
  static const AwardType AwardType_MIN =
    UnityWhipRankAward_AwardType_AwardType_MIN;
  static const AwardType AwardType_MAX =
    UnityWhipRankAward_AwardType_AwardType_MAX;
  static const int AwardType_ARRAYSIZE =
    UnityWhipRankAward_AwardType_AwardType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  AwardType_descriptor() {
    return UnityWhipRankAward_AwardType_descriptor();
  }
  static inline const ::std::string& AwardType_Name(AwardType value) {
    return UnityWhipRankAward_AwardType_Name(value);
  }
  static inline bool AwardType_Parse(const ::std::string& name,
      AwardType* value) {
    return UnityWhipRankAward_AwardType_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.UnityWhipRankAward.Reward award = 1;
  inline int award_size() const;
  inline void clear_award();
  static const int kAwardFieldNumber = 1;
  inline const ::game_connection::UnityWhipRankAward_Reward& award(int index) const;
  inline ::game_connection::UnityWhipRankAward_Reward* mutable_award(int index);
  inline ::game_connection::UnityWhipRankAward_Reward* add_award();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityWhipRankAward_Reward >&
      award() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityWhipRankAward_Reward >*
      mutable_award();
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityWhipRankAward)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::UnityWhipRankAward_Reward > award_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityWhipRankAward_2eproto();
  friend void protobuf_AssignDesc_UnityWhipRankAward_2eproto();
  friend void protobuf_ShutdownFile_UnityWhipRankAward_2eproto();
  
  void InitAsDefaultInstance();
  static UnityWhipRankAward* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityWhipRankAward_Reward

// required int32 type = 1;
inline bool UnityWhipRankAward_Reward::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityWhipRankAward_Reward::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityWhipRankAward_Reward::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityWhipRankAward_Reward::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 UnityWhipRankAward_Reward::type() const {
  return type_;
}
inline void UnityWhipRankAward_Reward::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// required int32 object_id = 2;
inline bool UnityWhipRankAward_Reward::has_object_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityWhipRankAward_Reward::set_has_object_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityWhipRankAward_Reward::clear_has_object_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityWhipRankAward_Reward::clear_object_id() {
  object_id_ = 0;
  clear_has_object_id();
}
inline ::google::protobuf::int32 UnityWhipRankAward_Reward::object_id() const {
  return object_id_;
}
inline void UnityWhipRankAward_Reward::set_object_id(::google::protobuf::int32 value) {
  set_has_object_id();
  object_id_ = value;
}

// required int32 size = 3;
inline bool UnityWhipRankAward_Reward::has_size() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UnityWhipRankAward_Reward::set_has_size() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UnityWhipRankAward_Reward::clear_has_size() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UnityWhipRankAward_Reward::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 UnityWhipRankAward_Reward::size() const {
  return size_;
}
inline void UnityWhipRankAward_Reward::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
}

// required int32 order = 4;
inline bool UnityWhipRankAward_Reward::has_order() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UnityWhipRankAward_Reward::set_has_order() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UnityWhipRankAward_Reward::clear_has_order() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UnityWhipRankAward_Reward::clear_order() {
  order_ = 0;
  clear_has_order();
}
inline ::google::protobuf::int32 UnityWhipRankAward_Reward::order() const {
  return order_;
}
inline void UnityWhipRankAward_Reward::set_order(::google::protobuf::int32 value) {
  set_has_order();
  order_ = value;
}

// -------------------------------------------------------------------

// UnityWhipRankAward

// repeated .game_connection.UnityWhipRankAward.Reward award = 1;
inline int UnityWhipRankAward::award_size() const {
  return award_.size();
}
inline void UnityWhipRankAward::clear_award() {
  award_.Clear();
}
inline const ::game_connection::UnityWhipRankAward_Reward& UnityWhipRankAward::award(int index) const {
  return award_.Get(index);
}
inline ::game_connection::UnityWhipRankAward_Reward* UnityWhipRankAward::mutable_award(int index) {
  return award_.Mutable(index);
}
inline ::game_connection::UnityWhipRankAward_Reward* UnityWhipRankAward::add_award() {
  return award_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityWhipRankAward_Reward >&
UnityWhipRankAward::award() const {
  return award_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityWhipRankAward_Reward >*
UnityWhipRankAward::mutable_award() {
  return &award_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityWhipRankAward_traits>() {
  return ::game_connection::UnityWhipRankAward_traits_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityWhipRankAward_AwardType>() {
  return ::game_connection::UnityWhipRankAward_AwardType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityWhipRankAward_2eproto__INCLUDED
