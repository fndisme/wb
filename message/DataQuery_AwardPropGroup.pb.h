// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataQuery_AwardPropGroup.proto

#ifndef PROTOBUF_DataQuery_5fAwardPropGroup_2eproto__INCLUDED
#define PROTOBUF_DataQuery_5fAwardPropGroup_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataQuery_5fAwardPropGroup_2eproto();
void protobuf_AssignDesc_DataQuery_5fAwardPropGroup_2eproto();
void protobuf_ShutdownFile_DataQuery_5fAwardPropGroup_2eproto();

class DataQuery_AwardPropGroup;
class DataQuery_AwardPropGroup_Award;
class DataQuery_AwardPropGroup_MaterialAward;

enum DataQuery_AwardPropGroup_traits {
  DataQuery_AwardPropGroup_traits_value = 7039
};
bool DataQuery_AwardPropGroup_traits_IsValid(int value);
const DataQuery_AwardPropGroup_traits DataQuery_AwardPropGroup_traits_traits_MIN = DataQuery_AwardPropGroup_traits_value;
const DataQuery_AwardPropGroup_traits DataQuery_AwardPropGroup_traits_traits_MAX = DataQuery_AwardPropGroup_traits_value;
const int DataQuery_AwardPropGroup_traits_traits_ARRAYSIZE = DataQuery_AwardPropGroup_traits_traits_MAX + 1;

const ::google::protobuf::EnumDescriptor* DataQuery_AwardPropGroup_traits_descriptor();
inline const ::std::string& DataQuery_AwardPropGroup_traits_Name(DataQuery_AwardPropGroup_traits value) {
  return ::google::protobuf::internal::NameOfEnum(
    DataQuery_AwardPropGroup_traits_descriptor(), value);
}
inline bool DataQuery_AwardPropGroup_traits_Parse(
    const ::std::string& name, DataQuery_AwardPropGroup_traits* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DataQuery_AwardPropGroup_traits>(
    DataQuery_AwardPropGroup_traits_descriptor(), name, value);
}
// ===================================================================

class DataQuery_AwardPropGroup_Award : public ::google::protobuf::Message {
 public:
  DataQuery_AwardPropGroup_Award();
  virtual ~DataQuery_AwardPropGroup_Award();
  
  DataQuery_AwardPropGroup_Award(const DataQuery_AwardPropGroup_Award& from);
  
  inline DataQuery_AwardPropGroup_Award& operator=(const DataQuery_AwardPropGroup_Award& from) {
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
  static const DataQuery_AwardPropGroup_Award& default_instance();
  
  void Swap(DataQuery_AwardPropGroup_Award* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_AwardPropGroup_Award* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_AwardPropGroup_Award& from);
  void MergeFrom(const DataQuery_AwardPropGroup_Award& from);
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
  
  // required int32 object_id = 1;
  inline bool has_object_id() const;
  inline void clear_object_id();
  static const int kObjectIdFieldNumber = 1;
  inline ::google::protobuf::int32 object_id() const;
  inline void set_object_id(::google::protobuf::int32 value);
  
  // required int32 type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);
  
  // required bytes description = 3;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 3;
  inline const ::std::string& description() const;
  inline void set_description(const ::std::string& value);
  inline void set_description(const char* value);
  inline void set_description(const void* value, size_t size);
  inline ::std::string* mutable_description();
  inline ::std::string* release_description();
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_AwardPropGroup.Award)
 private:
  inline void set_has_object_id();
  inline void clear_has_object_id();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_description();
  inline void clear_has_description();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 object_id_;
  ::google::protobuf::int32 type_;
  ::std::string* description_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fAwardPropGroup_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_AwardPropGroup_Award* default_instance_;
};
// -------------------------------------------------------------------

class DataQuery_AwardPropGroup_MaterialAward : public ::google::protobuf::Message {
 public:
  DataQuery_AwardPropGroup_MaterialAward();
  virtual ~DataQuery_AwardPropGroup_MaterialAward();
  
  DataQuery_AwardPropGroup_MaterialAward(const DataQuery_AwardPropGroup_MaterialAward& from);
  
  inline DataQuery_AwardPropGroup_MaterialAward& operator=(const DataQuery_AwardPropGroup_MaterialAward& from) {
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
  static const DataQuery_AwardPropGroup_MaterialAward& default_instance();
  
  void Swap(DataQuery_AwardPropGroup_MaterialAward* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_AwardPropGroup_MaterialAward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_AwardPropGroup_MaterialAward& from);
  void MergeFrom(const DataQuery_AwardPropGroup_MaterialAward& from);
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
  
  // required int32 material_id = 1;
  inline bool has_material_id() const;
  inline void clear_material_id();
  static const int kMaterialIdFieldNumber = 1;
  inline ::google::protobuf::int32 material_id() const;
  inline void set_material_id(::google::protobuf::int32 value);
  
  // required bytes description = 2;
  inline bool has_description() const;
  inline void clear_description();
  static const int kDescriptionFieldNumber = 2;
  inline const ::std::string& description() const;
  inline void set_description(const ::std::string& value);
  inline void set_description(const char* value);
  inline void set_description(const void* value, size_t size);
  inline ::std::string* mutable_description();
  inline ::std::string* release_description();
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_AwardPropGroup.MaterialAward)
 private:
  inline void set_has_material_id();
  inline void clear_has_material_id();
  inline void set_has_description();
  inline void clear_has_description();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* description_;
  ::google::protobuf::int32 material_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fAwardPropGroup_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_AwardPropGroup_MaterialAward* default_instance_;
};
// -------------------------------------------------------------------

class DataQuery_AwardPropGroup : public ::google::protobuf::Message {
 public:
  DataQuery_AwardPropGroup();
  virtual ~DataQuery_AwardPropGroup();
  
  DataQuery_AwardPropGroup(const DataQuery_AwardPropGroup& from);
  
  inline DataQuery_AwardPropGroup& operator=(const DataQuery_AwardPropGroup& from) {
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
  static const DataQuery_AwardPropGroup& default_instance();
  
  void Swap(DataQuery_AwardPropGroup* other);
  
  // implements Message ----------------------------------------------
  
  DataQuery_AwardPropGroup* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DataQuery_AwardPropGroup& from);
  void MergeFrom(const DataQuery_AwardPropGroup& from);
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
  
  typedef DataQuery_AwardPropGroup_Award Award;
  typedef DataQuery_AwardPropGroup_MaterialAward MaterialAward;
  
  typedef DataQuery_AwardPropGroup_traits traits;
  static const traits value = DataQuery_AwardPropGroup_traits_value;
  static inline bool traits_IsValid(int value) {
    return DataQuery_AwardPropGroup_traits_IsValid(value);
  }
  static const traits traits_MIN =
    DataQuery_AwardPropGroup_traits_traits_MIN;
  static const traits traits_MAX =
    DataQuery_AwardPropGroup_traits_traits_MAX;
  static const int traits_ARRAYSIZE =
    DataQuery_AwardPropGroup_traits_traits_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  traits_descriptor() {
    return DataQuery_AwardPropGroup_traits_descriptor();
  }
  static inline const ::std::string& traits_Name(traits value) {
    return DataQuery_AwardPropGroup_traits_Name(value);
  }
  static inline bool traits_Parse(const ::std::string& name,
      traits* value) {
    return DataQuery_AwardPropGroup_traits_Parse(name, value);
  }
  
  // accessors -------------------------------------------------------
  
  // repeated .game_connection.DataQuery_AwardPropGroup.Award award = 1;
  inline int award_size() const;
  inline void clear_award();
  static const int kAwardFieldNumber = 1;
  inline const ::game_connection::DataQuery_AwardPropGroup_Award& award(int index) const;
  inline ::game_connection::DataQuery_AwardPropGroup_Award* mutable_award(int index);
  inline ::game_connection::DataQuery_AwardPropGroup_Award* add_award();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_Award >&
      award() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_Award >*
      mutable_award();
  
  // repeated .game_connection.DataQuery_AwardPropGroup.MaterialAward material_award = 2;
  inline int material_award_size() const;
  inline void clear_material_award();
  static const int kMaterialAwardFieldNumber = 2;
  inline const ::game_connection::DataQuery_AwardPropGroup_MaterialAward& material_award(int index) const;
  inline ::game_connection::DataQuery_AwardPropGroup_MaterialAward* mutable_material_award(int index);
  inline ::game_connection::DataQuery_AwardPropGroup_MaterialAward* add_material_award();
  inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_MaterialAward >&
      material_award() const;
  inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_MaterialAward >*
      mutable_material_award();
  
  // @@protoc_insertion_point(class_scope:game_connection.DataQuery_AwardPropGroup)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_Award > award_;
  ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_MaterialAward > material_award_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_AssignDesc_DataQuery_5fAwardPropGroup_2eproto();
  friend void protobuf_ShutdownFile_DataQuery_5fAwardPropGroup_2eproto();
  
  void InitAsDefaultInstance();
  static DataQuery_AwardPropGroup* default_instance_;
};
// ===================================================================


// ===================================================================

// DataQuery_AwardPropGroup_Award

// required int32 object_id = 1;
inline bool DataQuery_AwardPropGroup_Award::has_object_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataQuery_AwardPropGroup_Award::set_has_object_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataQuery_AwardPropGroup_Award::clear_has_object_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataQuery_AwardPropGroup_Award::clear_object_id() {
  object_id_ = 0;
  clear_has_object_id();
}
inline ::google::protobuf::int32 DataQuery_AwardPropGroup_Award::object_id() const {
  return object_id_;
}
inline void DataQuery_AwardPropGroup_Award::set_object_id(::google::protobuf::int32 value) {
  set_has_object_id();
  object_id_ = value;
}

// required int32 type = 2;
inline bool DataQuery_AwardPropGroup_Award::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataQuery_AwardPropGroup_Award::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataQuery_AwardPropGroup_Award::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataQuery_AwardPropGroup_Award::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 DataQuery_AwardPropGroup_Award::type() const {
  return type_;
}
inline void DataQuery_AwardPropGroup_Award::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// required bytes description = 3;
inline bool DataQuery_AwardPropGroup_Award::has_description() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DataQuery_AwardPropGroup_Award::set_has_description() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DataQuery_AwardPropGroup_Award::clear_has_description() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DataQuery_AwardPropGroup_Award::clear_description() {
  if (description_ != &::google::protobuf::internal::kEmptyString) {
    description_->clear();
  }
  clear_has_description();
}
inline const ::std::string& DataQuery_AwardPropGroup_Award::description() const {
  return *description_;
}
inline void DataQuery_AwardPropGroup_Award::set_description(const ::std::string& value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void DataQuery_AwardPropGroup_Award::set_description(const char* value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void DataQuery_AwardPropGroup_Award::set_description(const void* value, size_t size) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DataQuery_AwardPropGroup_Award::mutable_description() {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  return description_;
}
inline ::std::string* DataQuery_AwardPropGroup_Award::release_description() {
  clear_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = description_;
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// DataQuery_AwardPropGroup_MaterialAward

// required int32 material_id = 1;
inline bool DataQuery_AwardPropGroup_MaterialAward::has_material_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_has_material_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DataQuery_AwardPropGroup_MaterialAward::clear_has_material_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DataQuery_AwardPropGroup_MaterialAward::clear_material_id() {
  material_id_ = 0;
  clear_has_material_id();
}
inline ::google::protobuf::int32 DataQuery_AwardPropGroup_MaterialAward::material_id() const {
  return material_id_;
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_material_id(::google::protobuf::int32 value) {
  set_has_material_id();
  material_id_ = value;
}

// required bytes description = 2;
inline bool DataQuery_AwardPropGroup_MaterialAward::has_description() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_has_description() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DataQuery_AwardPropGroup_MaterialAward::clear_has_description() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DataQuery_AwardPropGroup_MaterialAward::clear_description() {
  if (description_ != &::google::protobuf::internal::kEmptyString) {
    description_->clear();
  }
  clear_has_description();
}
inline const ::std::string& DataQuery_AwardPropGroup_MaterialAward::description() const {
  return *description_;
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_description(const ::std::string& value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_description(const char* value) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(value);
}
inline void DataQuery_AwardPropGroup_MaterialAward::set_description(const void* value, size_t size) {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  description_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DataQuery_AwardPropGroup_MaterialAward::mutable_description() {
  set_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    description_ = new ::std::string;
  }
  return description_;
}
inline ::std::string* DataQuery_AwardPropGroup_MaterialAward::release_description() {
  clear_has_description();
  if (description_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = description_;
    description_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// DataQuery_AwardPropGroup

// repeated .game_connection.DataQuery_AwardPropGroup.Award award = 1;
inline int DataQuery_AwardPropGroup::award_size() const {
  return award_.size();
}
inline void DataQuery_AwardPropGroup::clear_award() {
  award_.Clear();
}
inline const ::game_connection::DataQuery_AwardPropGroup_Award& DataQuery_AwardPropGroup::award(int index) const {
  return award_.Get(index);
}
inline ::game_connection::DataQuery_AwardPropGroup_Award* DataQuery_AwardPropGroup::mutable_award(int index) {
  return award_.Mutable(index);
}
inline ::game_connection::DataQuery_AwardPropGroup_Award* DataQuery_AwardPropGroup::add_award() {
  return award_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_Award >&
DataQuery_AwardPropGroup::award() const {
  return award_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_Award >*
DataQuery_AwardPropGroup::mutable_award() {
  return &award_;
}

// repeated .game_connection.DataQuery_AwardPropGroup.MaterialAward material_award = 2;
inline int DataQuery_AwardPropGroup::material_award_size() const {
  return material_award_.size();
}
inline void DataQuery_AwardPropGroup::clear_material_award() {
  material_award_.Clear();
}
inline const ::game_connection::DataQuery_AwardPropGroup_MaterialAward& DataQuery_AwardPropGroup::material_award(int index) const {
  return material_award_.Get(index);
}
inline ::game_connection::DataQuery_AwardPropGroup_MaterialAward* DataQuery_AwardPropGroup::mutable_material_award(int index) {
  return material_award_.Mutable(index);
}
inline ::game_connection::DataQuery_AwardPropGroup_MaterialAward* DataQuery_AwardPropGroup::add_material_award() {
  return material_award_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_MaterialAward >&
DataQuery_AwardPropGroup::material_award() const {
  return material_award_;
}
inline ::google::protobuf::RepeatedPtrField< ::game_connection::DataQuery_AwardPropGroup_MaterialAward >*
DataQuery_AwardPropGroup::mutable_material_award() {
  return &material_award_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace game_connection

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::game_connection::DataQuery_AwardPropGroup_traits>() {
  return ::game_connection::DataQuery_AwardPropGroup_traits_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataQuery_5fAwardPropGroup_2eproto__INCLUDED
