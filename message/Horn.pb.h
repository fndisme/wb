// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Horn.proto

#ifndef PROTOBUF_Horn_2eproto__INCLUDED
#define PROTOBUF_Horn_2eproto__INCLUDED

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
void  protobuf_AddDesc_Horn_2eproto();
void protobuf_AssignDesc_Horn_2eproto();
void protobuf_ShutdownFile_Horn_2eproto();

class Horn;

enum Horn_traits {
  Horn_traits_value = 3472
};
bool Horn_traits_IsValid(int value);
const Horn_traits Horn_traits_traits_MIN = Horn_traits_value;
const Horn_traits Horn_traits_traits_MAX = Horn_traits_value;
const int Horn_traits_traits_ARRAYSIZE = Horn_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* Horn_traits_descriptor();
inline const ::std::string& Horn_traits_Name(Horn_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    Horn_traits_descriptor(), value);
}
inline bool Horn_traits_Parse(
    const ::std::string& name, Horn_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Horn_traits>(
    Horn_traits_descriptor(), name, value);
}
// ===================================================================

class Horn : public ::google::protobuf::Message {
 public:
  Horn();
  virtual ~Horn();
  
  Horn(const Horn& from);
  
  inline Horn& operator=(const Horn& from) {
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
  static const Horn& default_instance();
  
  void Swap(Horn* other);
  
  // implements Message ----------------------------------------------
  
  Horn* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Horn& from);
  void MergeFrom(const Horn& from);
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
  
  typedef Horn_traits traits;
  static const traits value = Horn_traits_value;
  static inline bool traits_IsValid(int value) {
    return Horn_traits_IsValid(value);
  }
  static const traits traits_MIN =
    Horn_traits_traits_MIN;
  static const traits traits_MAX =
    Horn_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    Horn_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return Horn_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return Horn_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return Horn_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // required bool is_big = 1;
  inline bool has_is_big() const;
  inline void clear_is_big();
  static const int kIsBigFieldNumber = 1;
  inline bool is_big() const;
  inline void set_is_big(bool value);
  
  // required int32 player_id = 2;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 2;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);
  
  // required bytes information = 3;
  inline bool has_information() const;
  inline void clear_information();
  static const int kInformationFieldNumber = 3;
  inline const ::std::string& information() const;
  inline void set_information(const ::std::string& value);
  inline void set_information(const char* value);
  inline void set_information(const void* value, size_t size);
  inline ::std::string* mutable_information();
  inline ::std::string* release_information();
  
  // @@protoc_insertion_point(class_scope:game_connection.Horn)
 private:
  inline void set_has_is_big();
  inline void clear_has_is_big();
  inline void set_has_player_id();
  inline void clear_has_player_id();
  inline void set_has_information();
  inline void clear_has_information();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  bool is_big_;
  ::google::protobuf::int32 player_id_;
  ::std::string* information_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_Horn_2eproto();
  friend void protobuf_AssignDesc_Horn_2eproto();
  friend void protobuf_ShutdownFile_Horn_2eproto();
  
  void InitAsDefaultInstance();
  static Horn* default_instance_;
};
// ===================================================================


// ===================================================================

// Horn

// required bool is_big = 1;
inline bool Horn::has_is_big() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Horn::set_has_is_big() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Horn::clear_has_is_big() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Horn::clear_is_big() {
  is_big_ = false;
  clear_has_is_big();
}
inline bool Horn::is_big() const {
  return is_big_;
}
inline void Horn::set_is_big(bool value) {
  set_has_is_big();
  is_big_ = value;
}

// required int32 player_id = 2;
inline bool Horn::has_player_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Horn::set_has_player_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Horn::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Horn::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 Horn::player_id() const {
  return player_id_;
}
inline void Horn::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}

// required bytes information = 3;
inline bool Horn::has_information() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Horn::set_has_information() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Horn::clear_has_information() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Horn::clear_information() {
  if (information_ != &::google::protobuf::internal::kEmptyString) {
    information_->clear();
  }
  clear_has_information();
}
inline const ::std::string& Horn::information() const {
  return *information_;
}
inline void Horn::set_information(const ::std::string& value) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(value);
}
inline void Horn::set_information(const char* value) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(value);
}
inline void Horn::set_information(const void* value, size_t size) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Horn::mutable_information() {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  return information_;
}
inline ::std::string* Horn::release_information() {
  clear_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = information_;
    information_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::Horn_traits>() {
  return ::game_connection::Horn_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Horn_2eproto__INCLUDED
