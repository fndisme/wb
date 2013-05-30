// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataQuery_ArmyGroup.proto

#ifndef PROTOBUF_DataQuery_5fArmyGroup_2eproto__INCLUDED
#define PROTOBUF_DataQuery_5fArmyGroup_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataQuery_5fArmyGroup_2eproto();
void protobuf_AssignDesc_DataQuery_5fArmyGroup_2eproto();
void protobuf_ShutdownFile_DataQuery_5fArmyGroup_2eproto();

class DataQuery_ArmyGroup;
class DataQuery_ArmyGroup_GroupInformation;

enum DataQuery_ArmyGroup_traits {
  DataQuery_ArmyGroup_traits_value = 7523
};
bool DataQuery_ArmyGroup_traits_IsValid(int value);
const DataQuery_ArmyGroup_traits DataQuery_ArmyGroup_traits_traits_MIN = DataQuery_ArmyGroup_traits_value;
const DataQuery_ArmyGroup_traits DataQuery_ArmyGroup_traits_traits_MAX = DataQuery_ArmyGroup_traits_value;
const int DataQuery_ArmyGroup_traits_traits_ARRAYSIZE = DataQuery_ArmyGroup_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* DataQuery_ArmyGroup_traits_descriptor();
inline const ::std::string& DataQuery_ArmyGroup_traits_Name(DataQuery_ArmyGroup_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    DataQuery_ArmyGroup_traits_descriptor(), value);
}
inline bool DataQuery_ArmyGroup_traits_Parse(
    const ::std::string& name, DataQuery_ArmyGroup_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DataQuery_ArmyGroup_traits>(
    DataQuery_ArmyGroup_traits_descriptor(), name, value);
}
// ===================================================================

class DataQuery_ArmyGroup_GroupInformation : public ::google::protobuf::Message {
 public:
  DataQuery_ArmyGroup_GroupInformation();
  virtual ~DataQuery_ArmyGroup_GroupInformation();
  
  DataQuery_ArmyGroup_GroupInformation(const DataQuery_ArmyGroup_GroupInformation& from);
  
  inline DataQuery_ArmyGroup_GroupInformation& operator=(const DataQuery_ArmyGroup_GroupInformation& from) {
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
  static const DataQuery_ArmyGroup_GroupInformation& default_instance();
  
  void Swap(DataQuery_ArmyGroup_GroupInformation* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_ArmyGroup_GroupInformation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_ArmyGroup_GroupInformation& from);
  void MergeFrom(const DataQuery_ArmyGroup_GroupInformation& from);
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
  
  // required int32 chief_id = 2;
  inline bool has_chief_id() const;
  inline void clear_chief_id();
  static const int kChiefIdFieldNumber = 2;
  inline ::google::protobuf::int32 chief_id() const;
  inline void set_chief_id(::google::protobuf::int32 value);
  
  // required bytes name = 3;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 3;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const void* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_ArmyGroup.GroupInformation)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_chief_id();
  inline void clear_has_chief_id();
  inline void set_has_name();
  inline void clear_has_name();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 chief_id_;
  ::std::string* name_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fArmyGroup_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fArmyGroup_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fArmyGroup_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_ArmyGroup_GroupInformation* default_instance_;
};
// -------------------------------------------------------------------

class DataQuery_ArmyGroup : public ::google::protobuf::Message {
 public:
  DataQuery_ArmyGroup();
  virtual ~DataQuery_ArmyGroup();
  
  DataQuery_ArmyGroup(const DataQuery_ArmyGroup& from);
  
  inline DataQuery_ArmyGroup& operator=(const DataQuery_ArmyGroup& from) {
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
  static const DataQuery_ArmyGroup& default_instance();
  
  void Swap(DataQuery_ArmyGroup* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_ArmyGroup* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_ArmyGroup& from);
  void MergeFrom(const DataQuery_ArmyGroup& from);
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
  
  typedef DataQuery_ArmyGroup_GroupInformation GroupInformation;
  
  typedef DataQuery_ArmyGroup_traits traits;
  static const traits value = DataQuery_ArmyGroup_traits_value;
  static inline bool traits_IsValid(int value) {
    return DataQuery_ArmyGroup_traits_IsValid(value);
  }
  static const traits traits_MIN =
    DataQuery_ArmyGroup_traits_traits_MIN;
  static const traits traits_MAX =
    DataQuery_ArmyGroup_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    DataQuery_ArmyGroup_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return DataQuery_ArmyGroup_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return DataQuery_ArmyGroup_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return DataQuery_ArmyGroup_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.DataQuery_ArmyGroup.GroupInformation army = 1;
  inline int army_size() const;
  inline void clear_army();
  static const int kArmyFieldNumber = 1;
  inline const ::game_connection::DataQuery_ArmyGroup_GroupInformation& army(int index) const;
  inline ::game_connection::DataQuery_ArmyGroup_GroupInformation* mutable_army(int index);
  inline ::game_connection::DataQuery_ArmyGroup_GroupInformation* add_army();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_ArmyGroup_GroupInformation >&
      army() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_ArmyGroup_GroupInformation >*
      mutable_army();
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_ArmyGroup)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_ArmyGroup_GroupInformation > army_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fArmyGroup_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fArmyGroup_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fArmyGroup_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_ArmyGroup* default_instance_;
};
// ===================================================================


// ===================================================================

// DataQuery_ArmyGroup_GroupInformation

// required int32 id = 1;
inline bool DataQuery_ArmyGroup_GroupInformation::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 DataQuery_ArmyGroup_GroupInformation::id() const {
  return id_;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required int32 chief_id = 2;
inline bool DataQuery_ArmyGroup_GroupInformation::has_chief_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_has_chief_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_has_chief_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_chief_id() {
  chief_id_ = 0;
  clear_has_chief_id();
}
inline ::google::protobuf::int32 DataQuery_ArmyGroup_GroupInformation::chief_id() const {
  return chief_id_;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_chief_id(::google::protobuf::int32 value) {
  set_has_chief_id();
  chief_id_ = value;
}

// required bytes name = 3;
inline bool DataQuery_ArmyGroup_GroupInformation::has_name() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_has_name() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_has_name() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DataQuery_ArmyGroup_GroupInformation::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& DataQuery_ArmyGroup_GroupInformation::name() const {
  return *name_;
}
inline void DataQuery_ArmyGroup_GroupInformation::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void DataQuery_ArmyGroup_GroupInformation::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void DataQuery_ArmyGroup_GroupInformation::set_name(const void* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DataQuery_ArmyGroup_GroupInformation::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* DataQuery_ArmyGroup_GroupInformation::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// DataQuery_ArmyGroup

// repeated .game_connection.DataQuery_ArmyGroup.GroupInformation army = 1;
inline int DataQuery_ArmyGroup::army_size() const {
  return army_.size();
}
inline void DataQuery_ArmyGroup::clear_army() {
  army_.Clear();
}
inline const ::game_connection::DataQuery_ArmyGroup_GroupInformation& DataQuery_ArmyGroup::army(int index) const {
  return army_.Get(index);
}
inline ::game_connection::DataQuery_ArmyGroup_GroupInformation* DataQuery_ArmyGroup::mutable_army(int index) {
  return army_.Mutable(index);
}
inline ::game_connection::DataQuery_ArmyGroup_GroupInformation* DataQuery_ArmyGroup::add_army() {
  return army_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_ArmyGroup_GroupInformation >&
DataQuery_ArmyGroup::army() const {
  return army_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_ArmyGroup_GroupInformation >*
DataQuery_ArmyGroup::mutable_army() {
  return &army_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::DataQuery_ArmyGroup_traits>() {
  return ::game_connection::DataQuery_ArmyGroup_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataQuery_5fArmyGroup_2eproto__INCLUDED
