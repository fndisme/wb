// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityValidDailyBoss.proto

#ifndef PROTOBUF_UnityValidDailyBoss_2eproto__INCLUDED
#define PROTOBUF_UnityValidDailyBoss_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityValidDailyBoss_2eproto();
void protobuf_AssignDesc_UnityValidDailyBoss_2eproto();
void protobuf_ShutdownFile_UnityValidDailyBoss_2eproto();

class UnityValidDailyBoss;

enum UnityValidDailyBoss_traits {
  UnityValidDailyBoss_traits_value = 3254
};
bool UnityValidDailyBoss_traits_IsValid(int value);
const UnityValidDailyBoss_traits UnityValidDailyBoss_traits_traits_MIN = UnityValidDailyBoss_traits_value;
const UnityValidDailyBoss_traits UnityValidDailyBoss_traits_traits_MAX = UnityValidDailyBoss_traits_value;
const int UnityValidDailyBoss_traits_traits_ARRAYSIZE = UnityValidDailyBoss_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityValidDailyBoss_traits_descriptor();
inline const ::std::string& UnityValidDailyBoss_traits_Name(UnityValidDailyBoss_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityValidDailyBoss_traits_descriptor(), value);
}
inline bool UnityValidDailyBoss_traits_Parse(
    const ::std::string& name, UnityValidDailyBoss_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityValidDailyBoss_traits>(
    UnityValidDailyBoss_traits_descriptor(), name, value);
}
// ===================================================================

class UnityValidDailyBoss : public ::google::protobuf::Message {
 public:
  UnityValidDailyBoss();
  virtual ~UnityValidDailyBoss();
  
  UnityValidDailyBoss(const UnityValidDailyBoss& from);
  
  inline UnityValidDailyBoss& operator=(const UnityValidDailyBoss& from) {
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
  static const UnityValidDailyBoss& default_instance();
  
  void Swap(UnityValidDailyBoss* other);
  
  // implements Message ----------------------------------------------
  
  UnityValidDailyBoss* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityValidDailyBoss& from);
  void MergeFrom(const UnityValidDailyBoss& from);
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
  
  typedef UnityValidDailyBoss_traits traits;
  static const traits value = UnityValidDailyBoss_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityValidDailyBoss_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityValidDailyBoss_traits_traits_MIN;
  static const traits traits_MAX =
    UnityValidDailyBoss_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityValidDailyBoss_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityValidDailyBoss_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityValidDailyBoss_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityValidDailyBoss_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated int32 id = 1;
  inline int id_size() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id(int index) const;
  inline void set_id(int index, ::google::protobuf::int32 value);
  inline void add_id(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      id() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_id();
  
  // optional int32 current_time = 2;
  inline bool has_current_time() const;
  inline void clear_current_time();
  static const int kCurrentTimeFieldNumber = 2;
  inline ::google::protobuf::int32 current_time() const;
  inline void set_current_time(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityValidDailyBoss)
 private:
  inline void set_has_current_time();
  inline void clear_has_current_time();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > id_;
  ::google::protobuf::int32 current_time_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityValidDailyBoss_2eproto();
  friend void protobuf_AssignDesc_UnityValidDailyBoss_2eproto();
  friend void protobuf_ShutdownFile_UnityValidDailyBoss_2eproto();
  
  void InitAsDefaultInstance();
  static UnityValidDailyBoss* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityValidDailyBoss

// repeated int32 id = 1;
inline int UnityValidDailyBoss::id_size() const {
  return id_.size();
}
inline void UnityValidDailyBoss::clear_id() {
  id_.Clear();
}
inline ::google::protobuf::int32 UnityValidDailyBoss::id(int index) const {
  return id_.Get(index);
}
inline void UnityValidDailyBoss::set_id(int index, ::google::protobuf::int32 value) {
  id_.Set(index, value);
}
inline void UnityValidDailyBoss::add_id(::google::protobuf::int32 value) {
  id_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
UnityValidDailyBoss::id() const {
  return id_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
UnityValidDailyBoss::mutable_id() {
  return &id_;
}

// optional int32 current_time = 2;
inline bool UnityValidDailyBoss::has_current_time() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityValidDailyBoss::set_has_current_time() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityValidDailyBoss::clear_has_current_time() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityValidDailyBoss::clear_current_time() {
  current_time_ = 0;
  clear_has_current_time();
}
inline ::google::protobuf::int32 UnityValidDailyBoss::current_time() const {
  return current_time_;
}
inline void UnityValidDailyBoss::set_current_time(::google::protobuf::int32 value) {
  set_has_current_time();
  current_time_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityValidDailyBoss_traits>() {
  return ::game_connection::UnityValidDailyBoss_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityValidDailyBoss_2eproto__INCLUDED
