// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityUnfollowHall.proto

#ifndef PROTOBUF_UnityUnfollowHall_2eproto__INCLUDED
#define PROTOBUF_UnityUnfollowHall_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityUnfollowHall_2eproto();
void protobuf_AssignDesc_UnityUnfollowHall_2eproto();
void protobuf_ShutdownFile_UnityUnfollowHall_2eproto();

class UnityUnfollowHall;

enum UnityUnfollowHall_traits {
  UnityUnfollowHall_traits_value = 3433
};
bool UnityUnfollowHall_traits_IsValid(int value);
const UnityUnfollowHall_traits UnityUnfollowHall_traits_traits_MIN = UnityUnfollowHall_traits_value;
const UnityUnfollowHall_traits UnityUnfollowHall_traits_traits_MAX = UnityUnfollowHall_traits_value;
const int UnityUnfollowHall_traits_traits_ARRAYSIZE = UnityUnfollowHall_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityUnfollowHall_traits_descriptor();
inline const ::std::string& UnityUnfollowHall_traits_Name(UnityUnfollowHall_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityUnfollowHall_traits_descriptor(), value);
}
inline bool UnityUnfollowHall_traits_Parse(
    const ::std::string& name, UnityUnfollowHall_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityUnfollowHall_traits>(
    UnityUnfollowHall_traits_descriptor(), name, value);
}
// ===================================================================

class UnityUnfollowHall : public ::google::protobuf::Message {
 public:
  UnityUnfollowHall();
  virtual ~UnityUnfollowHall();
  
  UnityUnfollowHall(const UnityUnfollowHall& from);
  
  inline UnityUnfollowHall& operator=(const UnityUnfollowHall& from) {
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
  static const UnityUnfollowHall& default_instance();
  
  void Swap(UnityUnfollowHall* other);
  
  // implements Message ----------------------------------------------
  
  UnityUnfollowHall* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityUnfollowHall& from);
  void MergeFrom(const UnityUnfollowHall& from);
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
  
  typedef UnityUnfollowHall_traits traits;
  static const traits value = UnityUnfollowHall_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityUnfollowHall_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityUnfollowHall_traits_traits_MIN;
  static const traits traits_MAX =
    UnityUnfollowHall_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityUnfollowHall_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityUnfollowHall_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityUnfollowHall_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityUnfollowHall_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required bool unfollow_all = 2;
  inline bool has_unfollow_all() const;
  inline void clear_unfollow_all();
  static const int kUnfollowAllFieldNumber = 2;
  inline bool unfollow_all() const;
  inline void set_unfollow_all(bool value);
  
  // optional int32 not_follow_id = 1;
  inline bool has_not_follow_id() const;
  inline void clear_not_follow_id();
  static const int kNotFollowIdFieldNumber = 1;
  inline ::google::protobuf::int32 not_follow_id() const;
  inline void set_not_follow_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityUnfollowHall)
 private:
  inline void set_has_unfollow_all();
  inline void clear_has_unfollow_all();
  inline void set_has_not_follow_id();
  inline void clear_has_not_follow_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  bool unfollow_all_;
  ::google::protobuf::int32 not_follow_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityUnfollowHall_2eproto();
  friend void protobuf_AssignDesc_UnityUnfollowHall_2eproto();
  friend void protobuf_ShutdownFile_UnityUnfollowHall_2eproto();
  
  void InitAsDefaultInstance();
  static UnityUnfollowHall* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityUnfollowHall

// required bool unfollow_all = 2;
inline bool UnityUnfollowHall::has_unfollow_all() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityUnfollowHall::set_has_unfollow_all() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityUnfollowHall::clear_has_unfollow_all() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityUnfollowHall::clear_unfollow_all() {
  unfollow_all_ = false;
  clear_has_unfollow_all();
}
inline bool UnityUnfollowHall::unfollow_all() const {
  return unfollow_all_;
}
inline void UnityUnfollowHall::set_unfollow_all(bool value) {
  set_has_unfollow_all();
  unfollow_all_ = value;
}

// optional int32 not_follow_id = 1;
inline bool UnityUnfollowHall::has_not_follow_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityUnfollowHall::set_has_not_follow_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityUnfollowHall::clear_has_not_follow_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityUnfollowHall::clear_not_follow_id() {
  not_follow_id_ = 0;
  clear_has_not_follow_id();
}
inline ::google::protobuf::int32 UnityUnfollowHall::not_follow_id() const {
  return not_follow_id_;
}
inline void UnityUnfollowHall::set_not_follow_id(::google::protobuf::int32 value) {
  set_has_not_follow_id();
  not_follow_id_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityUnfollowHall_traits>() {
  return ::game_connection::UnityUnfollowHall_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityUnfollowHall_2eproto__INCLUDED
