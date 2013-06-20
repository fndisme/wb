// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: HeartBeat.proto

#ifndef PROTOBUF_HeartBeat_2eproto__INCLUDED
#define PROTOBUF_HeartBeat_2eproto__INCLUDED

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
void  protobuf_AddDesc_HeartBeat_2eproto();
void protobuf_AssignDesc_HeartBeat_2eproto();
void protobuf_ShutdownFile_HeartBeat_2eproto();

class HeartBeat;

enum HeartBeat_traits {
  HeartBeat_traits_value = 1
};
bool HeartBeat_traits_IsValid(int value);
const HeartBeat_traits HeartBeat_traits_traits_MIN = HeartBeat_traits_value;
const HeartBeat_traits HeartBeat_traits_traits_MAX = HeartBeat_traits_value;
const int HeartBeat_traits_traits_ARRAYSIZE = HeartBeat_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* HeartBeat_traits_descriptor();
inline const ::std::string& HeartBeat_traits_Name(HeartBeat_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    HeartBeat_traits_descriptor(), value);
}
inline bool HeartBeat_traits_Parse(
    const ::std::string& name, HeartBeat_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<HeartBeat_traits>(
    HeartBeat_traits_descriptor(), name, value);
}
// ===================================================================

class HeartBeat : public ::google::protobuf::Message {
 public:
  HeartBeat();
  virtual ~HeartBeat();

  HeartBeat(const HeartBeat& from);

  inline HeartBeat& operator=(const HeartBeat& from) {
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
  static const HeartBeat& default_instance();

  void Swap(HeartBeat* other);

  // implements Message ----------------------------------------------

  HeartBeat* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const HeartBeat& from);
  void MergeFrom(const HeartBeat& from);
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

  typedef HeartBeat_traits traits;
  static const traits value = HeartBeat_traits_value;
  static inline bool traits_IsValid(int value) {
    return HeartBeat_traits_IsValid(value);
  }
  static const traits traits_MIN =
    HeartBeat_traits_traits_MIN;
  static const traits traits_MAX =
    HeartBeat_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    HeartBeat_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return HeartBeat_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return HeartBeat_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return HeartBeat_traits_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:WebGame.Server.Stock.HeartBeat)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_HeartBeat_2eproto();
  friend void protobuf_AssignDesc_HeartBeat_2eproto();
  friend void protobuf_ShutdownFile_HeartBeat_2eproto();

  void InitAsDefaultInstance();
  static HeartBeat* default_instance_;
};
// ===================================================================


// ===================================================================

// HeartBeat


// @@protoc_insertion_point(namespace_scope)

}  // namespace Stock
}  // namespace Server
}  // namespace WebGame

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::WebGame::Server::Stock::HeartBeat_traits>() {
  return ::WebGame::Server::Stock::HeartBeat_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_HeartBeat_2eproto__INCLUDED
