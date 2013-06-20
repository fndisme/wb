// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: InnerMessage.proto

#ifndef PROTOBUF_InnerMessage_2eproto__INCLUDED
#define PROTOBUF_InnerMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace WebGame {
namespace Server {
namespace Stock {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_InnerMessage_2eproto();
void protobuf_AssignDesc_InnerMessage_2eproto();
void protobuf_ShutdownFile_InnerMessage_2eproto();

class InnerMessage;

enum InnerMessage_traits {
  InnerMessage_traits_value = 2
};
bool InnerMessage_traits_IsValid(int value);
const InnerMessage_traits InnerMessage_traits_traits_MIN = InnerMessage_traits_value;
const InnerMessage_traits InnerMessage_traits_traits_MAX = InnerMessage_traits_value;
const int InnerMessage_traits_traits_ARRAYSIZE = InnerMessage_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* InnerMessage_traits_descriptor();
inline const ::std::string& InnerMessage_traits_Name(InnerMessage_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    InnerMessage_traits_descriptor(), value);
}
inline bool InnerMessage_traits_Parse(
    const ::std::string& name, InnerMessage_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<InnerMessage_traits>(
    InnerMessage_traits_descriptor(), name, value);
}
// ===================================================================

class InnerMessage : public ::google::protobuf::Message {
 public:
  InnerMessage();
  virtual ~InnerMessage();

  InnerMessage(const InnerMessage& from);

  inline InnerMessage& operator=(const InnerMessage& from) {
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
  static const InnerMessage& default_instance();

  void Swap(InnerMessage* other);

  // implements Message ----------------------------------------------

  InnerMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const InnerMessage& from);
  void MergeFrom(const InnerMessage& from);
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

  typedef InnerMessage_traits traits;
  static const traits value = InnerMessage_traits_value;
  static inline bool traits_IsValid(int value) {
    return InnerMessage_traits_IsValid(value);
  }
  static const traits traits_MIN =
    InnerMessage_traits_traits_MIN;
  static const traits traits_MAX =
    InnerMessage_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    InnerMessage_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return InnerMessage_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return InnerMessage_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return InnerMessage_traits_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required bytes information = 1;
  inline bool has_information() const;
  inline void clear_information();
  static const int kInformationFieldNumber = 1;
  inline const ::std::string& information() const;
  inline void set_information(const ::std::string& value);
  inline void set_information(const char* value);
  inline void set_information(const void* value, size_t size);
  inline ::std::string* mutable_information();
  inline ::std::string* release_information();
  inline void set_allocated_information(::std::string* information);

  // @@protoc_insertion_point(class_scope:WebGame.Server.Stock.InnerMessage)
 private:
  inline void set_has_information();
  inline void clear_has_information();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* information_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_InnerMessage_2eproto();
  friend void protobuf_AssignDesc_InnerMessage_2eproto();
  friend void protobuf_ShutdownFile_InnerMessage_2eproto();

  void InitAsDefaultInstance();
  static InnerMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// InnerMessage

// required bytes information = 1;
inline bool InnerMessage::has_information() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void InnerMessage::set_has_information() {
  _has_bits_[0] |= 0x00000001u;
}
inline void InnerMessage::clear_has_information() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void InnerMessage::clear_information() {
  if (information_ != &::google::protobuf::internal::kEmptyString) {
    information_->clear();
  }
  clear_has_information();
}
inline const ::std::string& InnerMessage::information() const {
  return *information_;
}
inline void InnerMessage::set_information(const ::std::string& value) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(value);
}
inline void InnerMessage::set_information(const char* value) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(value);
}
inline void InnerMessage::set_information(const void* value, size_t size) {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  information_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* InnerMessage::mutable_information() {
  set_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    information_ = new ::std::string;
  }
  return information_;
}
inline ::std::string* InnerMessage::release_information() {
  clear_has_information();
  if (information_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = information_;
    information_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void InnerMessage::set_allocated_information(::std::string* information) {
  if (information_ != &::google::protobuf::internal::kEmptyString) {
    delete information_;
  }
  if (information) {
    set_has_information();
    information_ = information;
  } else {
    clear_has_information();
    information_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Stock
}  // namespace Server
}  // namespace WebGame

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::WebGame::Server::Stock::InnerMessage_traits>() {
  return ::WebGame::Server::Stock::InnerMessage_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_InnerMessage_2eproto__INCLUDED
