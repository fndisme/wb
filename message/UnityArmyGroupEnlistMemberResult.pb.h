// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityArmyGroupEnlistMemberResult.proto

#ifndef PROTOBUF_UnityArmyGroupEnlistMemberResult_2eproto__INCLUDED
#define PROTOBUF_UnityArmyGroupEnlistMemberResult_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityArmyGroupEnlistMemberResult_2eproto();
void protobuf_AssignDesc_UnityArmyGroupEnlistMemberResult_2eproto();
void protobuf_ShutdownFile_UnityArmyGroupEnlistMemberResult_2eproto();

class UnityArmyGroupEnlistMemberResult;

enum UnityArmyGroupEnlistMemberResult_traits {
  UnityArmyGroupEnlistMemberResult_traits_value = 4329
};
bool UnityArmyGroupEnlistMemberResult_traits_IsValid(int value);
const UnityArmyGroupEnlistMemberResult_traits UnityArmyGroupEnlistMemberResult_traits_traits_MIN = UnityArmyGroupEnlistMemberResult_traits_value;
const UnityArmyGroupEnlistMemberResult_traits UnityArmyGroupEnlistMemberResult_traits_traits_MAX = UnityArmyGroupEnlistMemberResult_traits_value;
const int UnityArmyGroupEnlistMemberResult_traits_traits_ARRAYSIZE = UnityArmyGroupEnlistMemberResult_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityArmyGroupEnlistMemberResult_traits_descriptor();
inline const ::std::string& UnityArmyGroupEnlistMemberResult_traits_Name(UnityArmyGroupEnlistMemberResult_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityArmyGroupEnlistMemberResult_traits_descriptor(), value);
}
inline bool UnityArmyGroupEnlistMemberResult_traits_Parse(
    const ::std::string& name, UnityArmyGroupEnlistMemberResult_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityArmyGroupEnlistMemberResult_traits>(
    UnityArmyGroupEnlistMemberResult_traits_descriptor(), name, value);
}
// ===================================================================

class UnityArmyGroupEnlistMemberResult : public ::google::protobuf::Message {
 public:
  UnityArmyGroupEnlistMemberResult();
  virtual ~UnityArmyGroupEnlistMemberResult();
  
  UnityArmyGroupEnlistMemberResult(const UnityArmyGroupEnlistMemberResult& from);
  
  inline UnityArmyGroupEnlistMemberResult& operator=(const UnityArmyGroupEnlistMemberResult& from) {
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
  static const UnityArmyGroupEnlistMemberResult& default_instance();
  
  void Swap(UnityArmyGroupEnlistMemberResult* other);
  
  // implements Message ----------------------------------------------
  
  UnityArmyGroupEnlistMemberResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityArmyGroupEnlistMemberResult& from);
  void MergeFrom(const UnityArmyGroupEnlistMemberResult& from);
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
  
  typedef UnityArmyGroupEnlistMemberResult_traits traits;
  static const traits value = UnityArmyGroupEnlistMemberResult_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityArmyGroupEnlistMemberResult_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityArmyGroupEnlistMemberResult_traits_traits_MIN;
  static const traits traits_MAX =
    UnityArmyGroupEnlistMemberResult_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityArmyGroupEnlistMemberResult_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityArmyGroupEnlistMemberResult_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityArmyGroupEnlistMemberResult_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityArmyGroupEnlistMemberResult_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required bool result = 1;
  inline bool has_result() const;
  inline void clear_result();
  static const int kResultFieldNumber = 1;
  inline bool result() const;
  inline void set_result(bool value);
  
  // optional int32 failed_reason = 2;
  inline bool has_failed_reason() const;
  inline void clear_failed_reason();
  static const int kFailedReasonFieldNumber = 2;
  inline ::google::protobuf::int32 failed_reason() const;
  inline void set_failed_reason(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityArmyGroupEnlistMemberResult)
 private:
  inline void set_has_result();
  inline void clear_has_result();
  inline void set_has_failed_reason();
  inline void clear_has_failed_reason();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  bool result_;
  ::google::protobuf::int32 failed_reason_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityArmyGroupEnlistMemberResult_2eproto();
  friend void protobuf_AssignDesc_UnityArmyGroupEnlistMemberResult_2eproto();
  friend void protobuf_ShutdownFile_UnityArmyGroupEnlistMemberResult_2eproto();
  
  void InitAsDefaultInstance();
  static UnityArmyGroupEnlistMemberResult* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityArmyGroupEnlistMemberResult

// required bool result = 1;
inline bool UnityArmyGroupEnlistMemberResult::has_result() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityArmyGroupEnlistMemberResult::set_has_result() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityArmyGroupEnlistMemberResult::clear_has_result() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityArmyGroupEnlistMemberResult::clear_result() {
  result_ = false;
  clear_has_result();
}
inline bool UnityArmyGroupEnlistMemberResult::result() const {
  return result_;
}
inline void UnityArmyGroupEnlistMemberResult::set_result(bool value) {
  set_has_result();
  result_ = value;
}

// optional int32 failed_reason = 2;
inline bool UnityArmyGroupEnlistMemberResult::has_failed_reason() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityArmyGroupEnlistMemberResult::set_has_failed_reason() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityArmyGroupEnlistMemberResult::clear_has_failed_reason() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityArmyGroupEnlistMemberResult::clear_failed_reason() {
  failed_reason_ = 0;
  clear_has_failed_reason();
}
inline ::google::protobuf::int32 UnityArmyGroupEnlistMemberResult::failed_reason() const {
  return failed_reason_;
}
inline void UnityArmyGroupEnlistMemberResult::set_failed_reason(::google::protobuf::int32 value) {
  set_has_failed_reason();
  failed_reason_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityArmyGroupEnlistMemberResult_traits>() {
  return ::game_connection::UnityArmyGroupEnlistMemberResult_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityArmyGroupEnlistMemberResult_2eproto__INCLUDED
