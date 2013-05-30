// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Platform_RefreshChallengeGroup.proto

#ifndef PROTOBUF_Platform_5fRefreshChallengeGroup_2eproto__INCLUDED
#define PROTOBUF_Platform_5fRefreshChallengeGroup_2eproto__INCLUDED

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
void  protobuf_AddDesc_Platform_5fRefreshChallengeGroup_2eproto();
void protobuf_AssignDesc_Platform_5fRefreshChallengeGroup_2eproto();
void protobuf_ShutdownFile_Platform_5fRefreshChallengeGroup_2eproto();

class Platform_RefreshChallengeGroup;

enum Platform_RefreshChallengeGroup_traits {
  Platform_RefreshChallengeGroup_traits_value = 5029
};
bool Platform_RefreshChallengeGroup_traits_IsValid(int value);
const Platform_RefreshChallengeGroup_traits Platform_RefreshChallengeGroup_traits_traits_MIN = Platform_RefreshChallengeGroup_traits_value;
const Platform_RefreshChallengeGroup_traits Platform_RefreshChallengeGroup_traits_traits_MAX = Platform_RefreshChallengeGroup_traits_value;
const int Platform_RefreshChallengeGroup_traits_traits_ARRAYSIZE = Platform_RefreshChallengeGroup_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* Platform_RefreshChallengeGroup_traits_descriptor();
inline const ::std::string& Platform_RefreshChallengeGroup_traits_Name(Platform_RefreshChallengeGroup_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    Platform_RefreshChallengeGroup_traits_descriptor(), value);
}
inline bool Platform_RefreshChallengeGroup_traits_Parse(
    const ::std::string& name, Platform_RefreshChallengeGroup_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Platform_RefreshChallengeGroup_traits>(
    Platform_RefreshChallengeGroup_traits_descriptor(), name, value);
}
// ===================================================================

class Platform_RefreshChallengeGroup : public ::google::protobuf::Message {
 public:
  Platform_RefreshChallengeGroup();
  virtual ~Platform_RefreshChallengeGroup();
  
  Platform_RefreshChallengeGroup(const Platform_RefreshChallengeGroup& from);
  
  inline Platform_RefreshChallengeGroup& operator=(const Platform_RefreshChallengeGroup& from) {
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
  static const Platform_RefreshChallengeGroup& default_instance();
  
  void Swap(Platform_RefreshChallengeGroup* other);
  
  // implements Message ----------------------------------------------
  
  Platform_RefreshChallengeGroup* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Platform_RefreshChallengeGroup& from);
  void MergeFrom(const Platform_RefreshChallengeGroup& from);
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
  
  typedef Platform_RefreshChallengeGroup_traits traits;
  static const traits value = Platform_RefreshChallengeGroup_traits_value;
  static inline bool traits_IsValid(int value) {
    return Platform_RefreshChallengeGroup_traits_IsValid(value);
  }
  static const traits traits_MIN =
    Platform_RefreshChallengeGroup_traits_traits_MIN;
  static const traits traits_MAX =
    Platform_RefreshChallengeGroup_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    Platform_RefreshChallengeGroup_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return Platform_RefreshChallengeGroup_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return Platform_RefreshChallengeGroup_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return Platform_RefreshChallengeGroup_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // @@protoc_insertion_point(class_scope:game_connection.Platform_RefreshChallengeGroup)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];
  
  friend void  protobuf_AddDesc_Platform_5fRefreshChallengeGroup_2eproto();
  friend void protobuf_AssignDesc_Platform_5fRefreshChallengeGroup_2eproto();
  friend void protobuf_ShutdownFile_Platform_5fRefreshChallengeGroup_2eproto();
  
  void InitAsDefaultInstance();
  static Platform_RefreshChallengeGroup* default_instance_;
};
// ===================================================================


// ===================================================================

// Platform_RefreshChallengeGroup


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::Platform_RefreshChallengeGroup_traits>() {
  return ::game_connection::Platform_RefreshChallengeGroup_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Platform_5fRefreshChallengeGroup_2eproto__INCLUDED
