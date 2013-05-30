// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityInitHallType.proto

#ifndef PROTOBUF_UnityInitHallType_2eproto__INCLUDED
#define PROTOBUF_UnityInitHallType_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityInitHallType_2eproto();
void protobuf_AssignDesc_UnityInitHallType_2eproto();
void protobuf_ShutdownFile_UnityInitHallType_2eproto();

class UnityInitHallType;

enum UnityInitHallType_traits {
  UnityInitHallType_traits_value = 4454
};
bool UnityInitHallType_traits_IsValid(int value);
const UnityInitHallType_traits UnityInitHallType_traits_traits_MIN = UnityInitHallType_traits_value;
const UnityInitHallType_traits UnityInitHallType_traits_traits_MAX = UnityInitHallType_traits_value;
const int UnityInitHallType_traits_traits_ARRAYSIZE = UnityInitHallType_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityInitHallType_traits_descriptor();
inline const ::std::string& UnityInitHallType_traits_Name(UnityInitHallType_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityInitHallType_traits_descriptor(), value);
}
inline bool UnityInitHallType_traits_Parse(
    const ::std::string& name, UnityInitHallType_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityInitHallType_traits>(
    UnityInitHallType_traits_descriptor(), name, value);
}
// ===================================================================

class UnityInitHallType : public ::google::protobuf::Message {
 public:
  UnityInitHallType();
  virtual ~UnityInitHallType();
  
  UnityInitHallType(const UnityInitHallType& from);
  
  inline UnityInitHallType& operator=(const UnityInitHallType& from) {
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
  static const UnityInitHallType& default_instance();
  
  void Swap(UnityInitHallType* other);
  
  // implements Message ----------------------------------------------
  
  UnityInitHallType* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityInitHallType& from);
  void MergeFrom(const UnityInitHallType& from);
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
  
  typedef UnityInitHallType_traits traits;
  static const traits value = UnityInitHallType_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityInitHallType_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityInitHallType_traits_traits_MIN;
  static const traits traits_MAX =
    UnityInitHallType_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityInitHallType_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityInitHallType_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityInitHallType_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityInitHallType_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);
  
  // optional bool with_hall_id = 2;
  inline bool has_with_hall_id() const;
  inline void clear_with_hall_id();
  static const int kWithHallIdFieldNumber = 2;
  inline bool with_hall_id() const;
  inline void set_with_hall_id(bool value);
  
  // optional int32 hall_id = 3;
  inline bool has_hall_id() const;
  inline void clear_hall_id();
  static const int kHallIdFieldNumber = 3;
  inline ::google::protobuf::int32 hall_id() const;
  inline void set_hall_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityInitHallType)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_with_hall_id();
  inline void clear_has_with_hall_id();
  inline void set_has_hall_id();
  inline void clear_has_hall_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 type_;
  bool with_hall_id_;
  ::google::protobuf::int32 hall_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityInitHallType_2eproto();
  friend void protobuf_AssignDesc_UnityInitHallType_2eproto();
  friend void protobuf_ShutdownFile_UnityInitHallType_2eproto();
  
  void InitAsDefaultInstance();
  static UnityInitHallType* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityInitHallType

// required int32 type = 1;
inline bool UnityInitHallType::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityInitHallType::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityInitHallType::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityInitHallType::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 UnityInitHallType::type() const {
  return type_;
}
inline void UnityInitHallType::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// optional bool with_hall_id = 2;
inline bool UnityInitHallType::has_with_hall_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityInitHallType::set_has_with_hall_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityInitHallType::clear_has_with_hall_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityInitHallType::clear_with_hall_id() {
  with_hall_id_ = false;
  clear_has_with_hall_id();
}
inline bool UnityInitHallType::with_hall_id() const {
  return with_hall_id_;
}
inline void UnityInitHallType::set_with_hall_id(bool value) {
  set_has_with_hall_id();
  with_hall_id_ = value;
}

// optional int32 hall_id = 3;
inline bool UnityInitHallType::has_hall_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UnityInitHallType::set_has_hall_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UnityInitHallType::clear_has_hall_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UnityInitHallType::clear_hall_id() {
  hall_id_ = 0;
  clear_has_hall_id();
}
inline ::google::protobuf::int32 UnityInitHallType::hall_id() const {
  return hall_id_;
}
inline void UnityInitHallType::set_hall_id(::google::protobuf::int32 value) {
  set_has_hall_id();
  hall_id_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityInitHallType_traits>() {
  return ::game_connection::UnityInitHallType_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityInitHallType_2eproto__INCLUDED
