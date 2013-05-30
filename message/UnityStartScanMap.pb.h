// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityStartScanMap.proto

#ifndef PROTOBUF_UnityStartScanMap_2eproto__INCLUDED
#define PROTOBUF_UnityStartScanMap_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityStartScanMap_2eproto();
void protobuf_AssignDesc_UnityStartScanMap_2eproto();
void protobuf_ShutdownFile_UnityStartScanMap_2eproto();

class UnityStartScanMap;

enum UnityStartScanMap_traits {
  UnityStartScanMap_traits_value = 3766
};
bool UnityStartScanMap_traits_IsValid(int value);
const UnityStartScanMap_traits UnityStartScanMap_traits_traits_MIN = UnityStartScanMap_traits_value;
const UnityStartScanMap_traits UnityStartScanMap_traits_traits_MAX = UnityStartScanMap_traits_value;
const int UnityStartScanMap_traits_traits_ARRAYSIZE = UnityStartScanMap_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityStartScanMap_traits_descriptor();
inline const ::std::string& UnityStartScanMap_traits_Name(UnityStartScanMap_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityStartScanMap_traits_descriptor(), value);
}
inline bool UnityStartScanMap_traits_Parse(
    const ::std::string& name, UnityStartScanMap_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityStartScanMap_traits>(
    UnityStartScanMap_traits_descriptor(), name, value);
}
// ===================================================================

class UnityStartScanMap : public ::google::protobuf::Message {
 public:
  UnityStartScanMap();
  virtual ~UnityStartScanMap();
  
  UnityStartScanMap(const UnityStartScanMap& from);
  
  inline UnityStartScanMap& operator=(const UnityStartScanMap& from) {
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
  static const UnityStartScanMap& default_instance();
  
  void Swap(UnityStartScanMap* other);
  
  // implements Message ----------------------------------------------
  
  UnityStartScanMap* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityStartScanMap& from);
  void MergeFrom(const UnityStartScanMap& from);
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
  
  typedef UnityStartScanMap_traits traits;
  static const traits value = UnityStartScanMap_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityStartScanMap_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityStartScanMap_traits_traits_MIN;
  static const traits traits_MAX =
    UnityStartScanMap_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityStartScanMap_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityStartScanMap_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityStartScanMap_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityStartScanMap_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required int32 dummy = 1;
  inline bool has_dummy() const;
  inline void clear_dummy();
  static const int kDummyFieldNumber = 1;
  inline ::google::protobuf::int32 dummy() const;
  inline void set_dummy(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityStartScanMap)
 private:
  inline void set_has_dummy();
  inline void clear_has_dummy();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 dummy_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityStartScanMap_2eproto();
  friend void protobuf_AssignDesc_UnityStartScanMap_2eproto();
  friend void protobuf_ShutdownFile_UnityStartScanMap_2eproto();
  
  void InitAsDefaultInstance();
  static UnityStartScanMap* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityStartScanMap

// required int32 dummy = 1;
inline bool UnityStartScanMap::has_dummy() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityStartScanMap::set_has_dummy() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityStartScanMap::clear_has_dummy() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityStartScanMap::clear_dummy() {
  dummy_ = 0;
  clear_has_dummy();
}
inline ::google::protobuf::int32 UnityStartScanMap::dummy() const {
  return dummy_;
}
inline void UnityStartScanMap::set_dummy(::google::protobuf::int32 value) {
  set_has_dummy();
  dummy_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityStartScanMap_traits>() {
  return ::game_connection::UnityStartScanMap_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityStartScanMap_2eproto__INCLUDED
