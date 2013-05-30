// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityQueryOnlineArmyGroupMember.proto

#ifndef PROTOBUF_UnityQueryOnlineArmyGroupMember_2eproto__INCLUDED
#define PROTOBUF_UnityQueryOnlineArmyGroupMember_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityQueryOnlineArmyGroupMember_2eproto();
void protobuf_AssignDesc_UnityQueryOnlineArmyGroupMember_2eproto();
void protobuf_ShutdownFile_UnityQueryOnlineArmyGroupMember_2eproto();

class UnityQueryOnlineArmyGroupMember;

enum UnityQueryOnlineArmyGroupMember_traits {
  UnityQueryOnlineArmyGroupMember_traits_value = 4455
};
bool UnityQueryOnlineArmyGroupMember_traits_IsValid(int value);
const UnityQueryOnlineArmyGroupMember_traits UnityQueryOnlineArmyGroupMember_traits_traits_MIN = UnityQueryOnlineArmyGroupMember_traits_value;
const UnityQueryOnlineArmyGroupMember_traits UnityQueryOnlineArmyGroupMember_traits_traits_MAX = UnityQueryOnlineArmyGroupMember_traits_value;
const int UnityQueryOnlineArmyGroupMember_traits_traits_ARRAYSIZE = UnityQueryOnlineArmyGroupMember_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityQueryOnlineArmyGroupMember_traits_descriptor();
inline const ::std::string& UnityQueryOnlineArmyGroupMember_traits_Name(UnityQueryOnlineArmyGroupMember_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityQueryOnlineArmyGroupMember_traits_descriptor(), value);
}
inline bool UnityQueryOnlineArmyGroupMember_traits_Parse(
    const ::std::string& name, UnityQueryOnlineArmyGroupMember_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityQueryOnlineArmyGroupMember_traits>(
    UnityQueryOnlineArmyGroupMember_traits_descriptor(), name, value);
}
// ===================================================================

class UnityQueryOnlineArmyGroupMember : public ::google::protobuf::Message {
 public:
  UnityQueryOnlineArmyGroupMember();
  virtual ~UnityQueryOnlineArmyGroupMember();
  
  UnityQueryOnlineArmyGroupMember(const UnityQueryOnlineArmyGroupMember& from);
  
  inline UnityQueryOnlineArmyGroupMember& operator=(const UnityQueryOnlineArmyGroupMember& from) {
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
  static const UnityQueryOnlineArmyGroupMember& default_instance();
  
  void Swap(UnityQueryOnlineArmyGroupMember* other);
  
  // implements Message ----------------------------------------------
  
  UnityQueryOnlineArmyGroupMember* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityQueryOnlineArmyGroupMember& from);
  void MergeFrom(const UnityQueryOnlineArmyGroupMember& from);
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
  
  typedef UnityQueryOnlineArmyGroupMember_traits traits;
  static const traits value = UnityQueryOnlineArmyGroupMember_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityQueryOnlineArmyGroupMember_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityQueryOnlineArmyGroupMember_traits_traits_MIN;
  static const traits traits_MAX =
    UnityQueryOnlineArmyGroupMember_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityQueryOnlineArmyGroupMember_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityQueryOnlineArmyGroupMember_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityQueryOnlineArmyGroupMember_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityQueryOnlineArmyGroupMember_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityQueryOnlineArmyGroupMember)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];
  
  friend void  protobuf_AddDesc_UnityQueryOnlineArmyGroupMember_2eproto();
  friend void protobuf_AssignDesc_UnityQueryOnlineArmyGroupMember_2eproto();
  friend void protobuf_ShutdownFile_UnityQueryOnlineArmyGroupMember_2eproto();
  
  void InitAsDefaultInstance();
  static UnityQueryOnlineArmyGroupMember* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityQueryOnlineArmyGroupMember


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityQueryOnlineArmyGroupMember_traits>() {
  return ::game_connection::UnityQueryOnlineArmyGroupMember_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityQueryOnlineArmyGroupMember_2eproto__INCLUDED
