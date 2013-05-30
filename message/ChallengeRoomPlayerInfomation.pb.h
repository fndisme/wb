// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ChallengeRoomPlayerInfomation.proto

#ifndef PROTOBUF_ChallengeRoomPlayerInfomation_2eproto__INCLUDED
#define PROTOBUF_ChallengeRoomPlayerInfomation_2eproto__INCLUDED

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
void  protobuf_AddDesc_ChallengeRoomPlayerInfomation_2eproto();
void protobuf_AssignDesc_ChallengeRoomPlayerInfomation_2eproto();
void protobuf_ShutdownFile_ChallengeRoomPlayerInfomation_2eproto();

class ChallengeRoomPlayerInfomation;

// ===================================================================

class ChallengeRoomPlayerInfomation : public ::google::protobuf::Message {
 public:
  ChallengeRoomPlayerInfomation();
  virtual ~ChallengeRoomPlayerInfomation();
  
  ChallengeRoomPlayerInfomation(const ChallengeRoomPlayerInfomation& from);
  
  inline ChallengeRoomPlayerInfomation& operator=(const ChallengeRoomPlayerInfomation& from) {
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
  static const ChallengeRoomPlayerInfomation& default_instance();
  
  void Swap(ChallengeRoomPlayerInfomation* other);
  
  // implements Message ----------------------------------------------
  
  ChallengeRoomPlayerInfomation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChallengeRoomPlayerInfomation& from);
  void MergeFrom(const ChallengeRoomPlayerInfomation& from);
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
  
  // required bool is_red_team = 2;
  inline bool has_is_red_team() const;
  inline void clear_is_red_team();
  static const int kIsRedTeamFieldNumber = 2;
  inline bool is_red_team() const;
  inline void set_is_red_team(bool value);
  
  // required bool is_ready = 3;
  inline bool has_is_ready() const;
  inline void clear_is_ready();
  static const int kIsReadyFieldNumber = 3;
  inline bool is_ready() const;
  inline void set_is_ready(bool value);
  
  // @@protoc_insertion_point(class_scope:game_connection.ChallengeRoomPlayerInfomation)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_is_red_team();
  inline void clear_has_is_red_team();
  inline void set_has_is_ready();
  inline void clear_has_is_ready();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 id_;
  bool is_red_team_;
  bool is_ready_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_ChallengeRoomPlayerInfomation_2eproto();
  friend void protobuf_AssignDesc_ChallengeRoomPlayerInfomation_2eproto();
  friend void protobuf_ShutdownFile_ChallengeRoomPlayerInfomation_2eproto();
  
  void InitAsDefaultInstance();
  static ChallengeRoomPlayerInfomation* default_instance_;
};
// ===================================================================


// ===================================================================

// ChallengeRoomPlayerInfomation

// required int32 id = 1;
inline bool ChallengeRoomPlayerInfomation::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChallengeRoomPlayerInfomation::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChallengeRoomPlayerInfomation::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChallengeRoomPlayerInfomation::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 ChallengeRoomPlayerInfomation::id() const {
  return id_;
}
inline void ChallengeRoomPlayerInfomation::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required bool is_red_team = 2;
inline bool ChallengeRoomPlayerInfomation::has_is_red_team() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChallengeRoomPlayerInfomation::set_has_is_red_team() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChallengeRoomPlayerInfomation::clear_has_is_red_team() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChallengeRoomPlayerInfomation::clear_is_red_team() {
  is_red_team_ = false;
  clear_has_is_red_team();
}
inline bool ChallengeRoomPlayerInfomation::is_red_team() const {
  return is_red_team_;
}
inline void ChallengeRoomPlayerInfomation::set_is_red_team(bool value) {
  set_has_is_red_team();
  is_red_team_ = value;
}

// required bool is_ready = 3;
inline bool ChallengeRoomPlayerInfomation::has_is_ready() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ChallengeRoomPlayerInfomation::set_has_is_ready() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ChallengeRoomPlayerInfomation::clear_has_is_ready() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ChallengeRoomPlayerInfomation::clear_is_ready() {
  is_ready_ = false;
  clear_has_is_ready();
}
inline bool ChallengeRoomPlayerInfomation::is_ready() const {
  return is_ready_;
}
inline void ChallengeRoomPlayerInfomation::set_is_ready(bool value) {
  set_has_is_ready();
  is_ready_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ChallengeRoomPlayerInfomation_2eproto__INCLUDED
