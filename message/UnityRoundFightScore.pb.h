// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UnityRoundFightScore.proto

#ifndef PROTOBUF_UnityRoundFightScore_2eproto__INCLUDED
#define PROTOBUF_UnityRoundFightScore_2eproto__INCLUDED

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
void  protobuf_AddDesc_UnityRoundFightScore_2eproto();
void protobuf_AssignDesc_UnityRoundFightScore_2eproto();
void protobuf_ShutdownFile_UnityRoundFightScore_2eproto();

class UnityRoundFightScore;
class UnityRoundFightScore_ScoreType;

enum UnityRoundFightScore_traits {
  UnityRoundFightScore_traits_value = 3851
};
bool UnityRoundFightScore_traits_IsValid(int value);
const UnityRoundFightScore_traits UnityRoundFightScore_traits_traits_MIN = UnityRoundFightScore_traits_value;
const UnityRoundFightScore_traits UnityRoundFightScore_traits_traits_MAX = UnityRoundFightScore_traits_value;
const int UnityRoundFightScore_traits_traits_ARRAYSIZE = UnityRoundFightScore_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* UnityRoundFightScore_traits_descriptor();
inline const ::std::string& UnityRoundFightScore_traits_Name(UnityRoundFightScore_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    UnityRoundFightScore_traits_descriptor(), value);
}
inline bool UnityRoundFightScore_traits_Parse(
    const ::std::string& name, UnityRoundFightScore_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UnityRoundFightScore_traits>(
    UnityRoundFightScore_traits_descriptor(), name, value);
}
// ===================================================================

class UnityRoundFightScore_ScoreType : public ::google::protobuf::Message {
 public:
  UnityRoundFightScore_ScoreType();
  virtual ~UnityRoundFightScore_ScoreType();
  
  UnityRoundFightScore_ScoreType(const UnityRoundFightScore_ScoreType& from);
  
  inline UnityRoundFightScore_ScoreType& operator=(const UnityRoundFightScore_ScoreType& from) {
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
  static const UnityRoundFightScore_ScoreType& default_instance();
  
  void Swap(UnityRoundFightScore_ScoreType* other);
  
  // implements Message ----------------------------------------------
  
  UnityRoundFightScore_ScoreType* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityRoundFightScore_ScoreType& from);
  void MergeFrom(const UnityRoundFightScore_ScoreType& from);
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
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // required int32 exp = 2;
  inline bool has_exp() const;
  inline void clear_exp();
  static const int kExpFieldNumber = 2;
  inline ::google::protobuf::int32 exp() const;
  inline void set_exp(::google::protobuf::int32 value);
  
  // required int32 server_id = 3;
  inline bool has_server_id() const;
  inline void clear_server_id();
  static const int kServerIdFieldNumber = 3;
  inline ::google::protobuf::int32 server_id() const;
  inline void set_server_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityRoundFightScore.ScoreType)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_exp();
  inline void clear_has_exp();
  inline void set_has_server_id();
  inline void clear_has_server_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 exp_;
  ::google::protobuf::int32 server_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityRoundFightScore_2eproto();
  friend void protobuf_AssignDesc_UnityRoundFightScore_2eproto();
  friend void protobuf_ShutdownFile_UnityRoundFightScore_2eproto();
  
  void InitAsDefaultInstance();
  static UnityRoundFightScore_ScoreType* default_instance_;
};
// -------------------------------------------------------------------

class UnityRoundFightScore : public ::google::protobuf::Message {
 public:
  UnityRoundFightScore();
  virtual ~UnityRoundFightScore();
  
  UnityRoundFightScore(const UnityRoundFightScore& from);
  
  inline UnityRoundFightScore& operator=(const UnityRoundFightScore& from) {
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
  static const UnityRoundFightScore& default_instance();
  
  void Swap(UnityRoundFightScore* other);
  
  // implements Message ----------------------------------------------
  
  UnityRoundFightScore* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UnityRoundFightScore& from);
  void MergeFrom(const UnityRoundFightScore& from);
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
  
  typedef UnityRoundFightScore_ScoreType ScoreType;
  
  typedef UnityRoundFightScore_traits traits;
  static const traits value = UnityRoundFightScore_traits_value;
  static inline bool traits_IsValid(int value) {
    return UnityRoundFightScore_traits_IsValid(value);
  }
  static const traits traits_MIN =
    UnityRoundFightScore_traits_traits_MIN;
  static const traits traits_MAX =
    UnityRoundFightScore_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    UnityRoundFightScore_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return UnityRoundFightScore_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return UnityRoundFightScore_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return UnityRoundFightScore_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.UnityRoundFightScore.ScoreType score = 1;
  inline int score_size() const;
  inline void clear_score();
  static const int kScoreFieldNumber = 1;
  inline const ::game_connection::UnityRoundFightScore_ScoreType& score(int index) const;
  inline ::game_connection::UnityRoundFightScore_ScoreType* mutable_score(int index);
  inline ::game_connection::UnityRoundFightScore_ScoreType* add_score();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityRoundFightScore_ScoreType >&
      score() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityRoundFightScore_ScoreType >*
      mutable_score();
  
  // @@protoc_insertion_point(class_scope:game_connection.UnityRoundFightScore)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::UnityRoundFightScore_ScoreType > score_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_UnityRoundFightScore_2eproto();
  friend void protobuf_AssignDesc_UnityRoundFightScore_2eproto();
  friend void protobuf_ShutdownFile_UnityRoundFightScore_2eproto();
  
  void InitAsDefaultInstance();
  static UnityRoundFightScore* default_instance_;
};
// ===================================================================


// ===================================================================

// UnityRoundFightScore_ScoreType

// required int32 id = 1;
inline bool UnityRoundFightScore_ScoreType::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UnityRoundFightScore_ScoreType::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UnityRoundFightScore_ScoreType::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UnityRoundFightScore_ScoreType::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 UnityRoundFightScore_ScoreType::id() const {
  return id_;
}
inline void UnityRoundFightScore_ScoreType::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required int32 exp = 2;
inline bool UnityRoundFightScore_ScoreType::has_exp() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UnityRoundFightScore_ScoreType::set_has_exp() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UnityRoundFightScore_ScoreType::clear_has_exp() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UnityRoundFightScore_ScoreType::clear_exp() {
  exp_ = 0;
  clear_has_exp();
}
inline ::google::protobuf::int32 UnityRoundFightScore_ScoreType::exp() const {
  return exp_;
}
inline void UnityRoundFightScore_ScoreType::set_exp(::google::protobuf::int32 value) {
  set_has_exp();
  exp_ = value;
}

// required int32 server_id = 3;
inline bool UnityRoundFightScore_ScoreType::has_server_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UnityRoundFightScore_ScoreType::set_has_server_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UnityRoundFightScore_ScoreType::clear_has_server_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UnityRoundFightScore_ScoreType::clear_server_id() {
  server_id_ = 0;
  clear_has_server_id();
}
inline ::google::protobuf::int32 UnityRoundFightScore_ScoreType::server_id() const {
  return server_id_;
}
inline void UnityRoundFightScore_ScoreType::set_server_id(::google::protobuf::int32 value) {
  set_has_server_id();
  server_id_ = value;
}

// -------------------------------------------------------------------

// UnityRoundFightScore

// repeated .game_connection.UnityRoundFightScore.ScoreType score = 1;
inline int UnityRoundFightScore::score_size() const {
  return score_.size();
}
inline void UnityRoundFightScore::clear_score() {
  score_.Clear();
}
inline const ::game_connection::UnityRoundFightScore_ScoreType& UnityRoundFightScore::score(int index) const {
  return score_.Get(index);
}
inline ::game_connection::UnityRoundFightScore_ScoreType* UnityRoundFightScore::mutable_score(int index) {
  return score_.Mutable(index);
}
inline ::game_connection::UnityRoundFightScore_ScoreType* UnityRoundFightScore::add_score() {
  return score_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::UnityRoundFightScore_ScoreType >&
UnityRoundFightScore::score() const {
  return score_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::UnityRoundFightScore_ScoreType >*
UnityRoundFightScore::mutable_score() {
  return &score_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::UnityRoundFightScore_traits>() {
  return ::game_connection::UnityRoundFightScore_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UnityRoundFightScore_2eproto__INCLUDED
