// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Platform_ArmyGroupStar.proto

#ifndef PROTOBUF_Platform_5fArmyGroupStar_2eproto__INCLUDED
#define PROTOBUF_Platform_5fArmyGroupStar_2eproto__INCLUDED

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
void  protobuf_AddDesc_Platform_5fArmyGroupStar_2eproto();
void protobuf_AssignDesc_Platform_5fArmyGroupStar_2eproto();
void protobuf_ShutdownFile_Platform_5fArmyGroupStar_2eproto();

class Platform_ArmyGroupStar;

enum Platform_ArmyGroupStar_traits {
  Platform_ArmyGroupStar_traits_value = 10122
};
bool Platform_ArmyGroupStar_traits_IsValid(int value);
const Platform_ArmyGroupStar_traits Platform_ArmyGroupStar_traits_traits_MIN = Platform_ArmyGroupStar_traits_value;
const Platform_ArmyGroupStar_traits Platform_ArmyGroupStar_traits_traits_MAX = Platform_ArmyGroupStar_traits_value;
const int Platform_ArmyGroupStar_traits_traits_ARRAYSIZE = Platform_ArmyGroupStar_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* Platform_ArmyGroupStar_traits_descriptor();
inline const ::std::string& Platform_ArmyGroupStar_traits_Name(Platform_ArmyGroupStar_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    Platform_ArmyGroupStar_traits_descriptor(), value);
}
inline bool Platform_ArmyGroupStar_traits_Parse(
    const ::std::string& name, Platform_ArmyGroupStar_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Platform_ArmyGroupStar_traits>(
    Platform_ArmyGroupStar_traits_descriptor(), name, value);
}
// ===================================================================

class Platform_ArmyGroupStar : public ::google::protobuf::Message {
 public:
  Platform_ArmyGroupStar();
  virtual ~Platform_ArmyGroupStar();
  
  Platform_ArmyGroupStar(const Platform_ArmyGroupStar& from);
  
  inline Platform_ArmyGroupStar& operator=(const Platform_ArmyGroupStar& from) {
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
  static const Platform_ArmyGroupStar& default_instance();
  
  void Swap(Platform_ArmyGroupStar* other);
  
  // implements Message ----------------------------------------------
  
  Platform_ArmyGroupStar* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Platform_ArmyGroupStar& from);
  void MergeFrom(const Platform_ArmyGroupStar& from);
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
  
  typedef Platform_ArmyGroupStar_traits traits;
  static const traits value = Platform_ArmyGroupStar_traits_value;
  static inline bool traits_IsValid(int value) {
    return Platform_ArmyGroupStar_traits_IsValid(value);
  }
  static const traits traits_MIN =
    Platform_ArmyGroupStar_traits_traits_MIN;
  static const traits traits_MAX =
    Platform_ArmyGroupStar_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    Platform_ArmyGroupStar_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return Platform_ArmyGroupStar_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return Platform_ArmyGroupStar_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return Platform_ArmyGroupStar_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 group_id = 1;
  inline bool has_group_id() const;
  inline void clear_group_id();
  static const int kGroupIdFieldNumber = 1;
  inline ::google::protobuf::int32 group_id() const;
  inline void set_group_id(::google::protobuf::int32 value);
  
  // required int32 star_id = 2;
  inline bool has_star_id() const;
  inline void clear_star_id();
  static const int kStarIdFieldNumber = 2;
  inline ::google::protobuf::int32 star_id() const;
  inline void set_star_id(::google::protobuf::int32 value);
  
  // required int32 size = 3;
  inline bool has_size() const;
  inline void clear_size();
  static const int kSizeFieldNumber = 3;
  inline ::google::protobuf::int32 size() const;
  inline void set_size(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.Platform_ArmyGroupStar)
 private:
  inline void set_has_group_id();
  inline void clear_has_group_id();
  inline void set_has_star_id();
  inline void clear_has_star_id();
  inline void set_has_size();
  inline void clear_has_size();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 group_id_;
  ::google::protobuf::int32 star_id_;
  ::google::protobuf::int32 size_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_Platform_5fArmyGroupStar_2eproto();
  friend void protobuf_AssignDesc_Platform_5fArmyGroupStar_2eproto();
  friend void protobuf_ShutdownFile_Platform_5fArmyGroupStar_2eproto();
  
  void InitAsDefaultInstance();
  static Platform_ArmyGroupStar* default_instance_;
};
// ===================================================================


// ===================================================================

// Platform_ArmyGroupStar

// required int32 group_id = 1;
inline bool Platform_ArmyGroupStar::has_group_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Platform_ArmyGroupStar::set_has_group_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Platform_ArmyGroupStar::clear_has_group_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Platform_ArmyGroupStar::clear_group_id() {
  group_id_ = 0;
  clear_has_group_id();
}
inline ::google::protobuf::int32 Platform_ArmyGroupStar::group_id() const {
  return group_id_;
}
inline void Platform_ArmyGroupStar::set_group_id(::google::protobuf::int32 value) {
  set_has_group_id();
  group_id_ = value;
}

// required int32 star_id = 2;
inline bool Platform_ArmyGroupStar::has_star_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Platform_ArmyGroupStar::set_has_star_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Platform_ArmyGroupStar::clear_has_star_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Platform_ArmyGroupStar::clear_star_id() {
  star_id_ = 0;
  clear_has_star_id();
}
inline ::google::protobuf::int32 Platform_ArmyGroupStar::star_id() const {
  return star_id_;
}
inline void Platform_ArmyGroupStar::set_star_id(::google::protobuf::int32 value) {
  set_has_star_id();
  star_id_ = value;
}

// required int32 size = 3;
inline bool Platform_ArmyGroupStar::has_size() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Platform_ArmyGroupStar::set_has_size() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Platform_ArmyGroupStar::clear_has_size() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Platform_ArmyGroupStar::clear_size() {
  size_ = 0;
  clear_has_size();
}
inline ::google::protobuf::int32 Platform_ArmyGroupStar::size() const {
  return size_;
}
inline void Platform_ArmyGroupStar::set_size(::google::protobuf::int32 value) {
  set_has_size();
  size_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::Platform_ArmyGroupStar_traits>() {
  return ::game_connection::Platform_ArmyGroupStar_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Platform_5fArmyGroupStar_2eproto__INCLUDED
