// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityCurrentHallCount.proto

#ifndef PROTOBUF_UnityCurrentHallCount_2eproto__INCLUDED
#define PROTOBUF_UnityCurrentHallCount_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityCurrentHallCount_2eproto();
void protobuf_AssignDesc_UnityCurrentHallCount_2eproto();
void protobuf_ShutdownFile_UnityCurrentHallCount_2eproto();

class UnityCurrentHallCount;
class UnityCurrentHallCount_HallCountInfomation;

enum UnityCurrentHallCount_traits {
  UnityCurrentHallCount_traits_value = 3523
};
bool UnityCurrentHallCount_traits_IsValid(int value);
const UnityCurrentHallCount_traits UnityCurrentHallCount_traits_traits_MIN = UnityCurrentHallCount_traits_value;
const UnityCurrentHallCount_traits UnityCurrentHallCount_traits_traits_MAX = UnityCurrentHallCount_traits_value;
const int UnityCurrentHallCount_traits_traits_ARRAYSIZE = UnityCurrentHallCount_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityCurrentHallCount_traits_descriptor();
inline const ::std::string& UnityCurrentHallCount_traits_Name(UnityCurrentHallCount_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityCurrentHallCount_traits_descriptor(), value);
}
inline bool UnityCurrentHallCount_traits_Parse(
    const ::std::string& name, UnityCurrentHallCount_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityCurrentHallCount_traits>(
    UnityCurrentHallCount_traits_descriptor(), name, value);
}
// ===================================================================

class UnityCurrentHallCount_HallCountInfomation : public ::google::protobuf::Message {
 public:
  UnityCurrentHallCount_HallCountInfomation();
  virtual ~UnityCurrentHallCount_HallCountInfomation();
  
  UnityCurrentHallCount_HallCountInfomation(const UnityCurrentHallCount_HallCountInfomation& from);
  
  inline UnityCurrentHallCount_HallCountInfomation& operator=(const UnityCurrentHallCount_HallCountInfomation& from) {
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
  static const UnityCurrentHallCount_HallCountInfomation& default_instance();
  
  void Swap(UnityCurrentHallCount_HallCountInfomation* other);
  
  // implements Message ----------------------------------------------
  
  UnityCurrentHallCount_HallCountInfomation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityCurrentHallCount_HallCountInfomation& from);
  void MergeFrom(const UnityCurrentHallCount_HallCountInfomation& from);
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
  
  // required int32 hall_size = 1;
  inline bool has_hall_size() const;
  inline void clear_hall_size();
  static const int kHallSizeFieldNumber = 1;
  inline ::google::protobuf::int32 hall_size() const;
  inline void set_hall_size(::google::protobuf::int32 value);
  
  // optional int32 hall_type = 2;
  inline bool has_hall_type() const;
  inline void clear_hall_type();
  static const int kHallTypeFieldNumber = 2;
  inline ::google::protobuf::int32 hall_type() const;
  inline void set_hall_type(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityCurrentHallCount.HallCountInfomation)
 private:
  inline void set_has_hall_size();
  inline void clear_has_hall_size();
  inline void set_has_hall_type();
  inline void clear_has_hall_type();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 hall_size_;
  ::google::protobuf::int32 hall_type_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityCurrentHallCount_2eproto();
  friend void protobuf_AssignDesc_UnityCurrentHallCount_2eproto();
  friend void protobuf_ShutdownFile_UnityCurrentHallCount_2eproto();
  
  void InitAsDefaultInstance();
  static UnityCurrentHallCount_HallCountInfomation* default_instance_;
};
// -------------------------------------------------------------------

class UnityCurrentHallCount : public ::google::protobuf::Message {
 public:
  UnityCurrentHallCount();
  virtual ~UnityCurrentHallCount();
  
  UnityCurrentHallCount(const UnityCurrentHallCount& from);
  
  inline UnityCurrentHallCount& operator=(const UnityCurrentHallCount& from) {
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
  static const UnityCurrentHallCount& default_instance();
  
  void Swap(UnityCurrentHallCount* other);
  
  // implements Message ----------------------------------------------
  
  UnityCurrentHallCount* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityCurrentHallCount& from);
  void MergeFrom(const UnityCurrentHallCount& from);
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
  
  typedef UnityCurrentHallCount_HallCountInfomation HallCountInfomation;
  
  typedef UnityCurrentHallCount_traits traits;
  static const traits value = UnityCurrentHallCount_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityCurrentHallCount_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityCurrentHallCount_traits_traits_MIN;
  static const traits traits_MAX =
    UnityCurrentHallCount_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityCurrentHallCount_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityCurrentHallCount_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityCurrentHallCount_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityCurrentHallCount_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.UnityCurrentHallCount.HallCountInfomation information = 1;
  inline int information_size() const;
  inline void clear_information();
  static const int kInformationFieldNumber = 1;
  inline const ::game_connection::UnityCurrentHallCount_HallCountInfomation& information(int index) const;
  inline ::game_connection::UnityCurrentHallCount_HallCountInfomation* mutable_information(int index);
  inline ::game_connection::UnityCurrentHallCount_HallCountInfomation* add_information();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityCurrentHallCount_HallCountInfomation >&
      information() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityCurrentHallCount_HallCountInfomation >*
      mutable_information();
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityCurrentHallCount)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::UnityCurrentHallCount_HallCountInfomation > information_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityCurrentHallCount_2eproto();
  friend void protobuf_AssignDesc_UnityCurrentHallCount_2eproto();
  friend void protobuf_ShutdownFile_UnityCurrentHallCount_2eproto();
  
  void InitAsDefaultInstance();
  static UnityCurrentHallCount* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityCurrentHallCount_HallCountInfomation

// required int32 hall_size = 1;
inline bool UnityCurrentHallCount_HallCountInfomation::has_hall_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityCurrentHallCount_HallCountInfomation::set_has_hall_size() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityCurrentHallCount_HallCountInfomation::clear_has_hall_size() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityCurrentHallCount_HallCountInfomation::clear_hall_size() {
  hall_size_ = 0;
  clear_has_hall_size();
}
inline ::google::protobuf::int32 UnityCurrentHallCount_HallCountInfomation::hall_size() const {
  return hall_size_;
}
inline void UnityCurrentHallCount_HallCountInfomation::set_hall_size(::google::protobuf::int32 value) {
  set_has_hall_size();
  hall_size_ = value;
}

// optional int32 hall_type = 2;
inline bool UnityCurrentHallCount_HallCountInfomation::has_hall_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityCurrentHallCount_HallCountInfomation::set_has_hall_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityCurrentHallCount_HallCountInfomation::clear_has_hall_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityCurrentHallCount_HallCountInfomation::clear_hall_type() {
  hall_type_ = 0;
  clear_has_hall_type();
}
inline ::google::protobuf::int32 UnityCurrentHallCount_HallCountInfomation::hall_type() const {
  return hall_type_;
}
inline void UnityCurrentHallCount_HallCountInfomation::set_hall_type(::google::protobuf::int32 value) {
  set_has_hall_type();
  hall_type_ = value;
}

// -------------------------------------------------------------------

// UnityCurrentHallCount

// repeated .game_connection.UnityCurrentHallCount.HallCountInfomation information = 1;
inline int UnityCurrentHallCount::information_size() const {
  return information_.size();
}
inline void UnityCurrentHallCount::clear_information() {
  information_.Clear();
}
inline const ::game_connection::UnityCurrentHallCount_HallCountInfomation& UnityCurrentHallCount::information(int index) const {
  return information_.Get(index);
}
inline ::game_connection::UnityCurrentHallCount_HallCountInfomation* UnityCurrentHallCount::mutable_information(int index) {
  return information_.Mutable(index);
}
inline ::game_connection::UnityCurrentHallCount_HallCountInfomation* UnityCurrentHallCount::add_information() {
  return information_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityCurrentHallCount_HallCountInfomation >&
UnityCurrentHallCount::information() const {
  return information_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityCurrentHallCount_HallCountInfomation >*
UnityCurrentHallCount::mutable_information() {
  return &information_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityCurrentHallCount_traits>() {
  return ::game_connection::UnityCurrentHallCount_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityCurrentHallCount_2eproto__INCLUDED
