// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: deepest.proto

#ifndef PROTOBUF_INCLUDED_deepest_2eproto
#define PROTOBUF_INCLUDED_deepest_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_deepest_2eproto 

namespace protobuf_deepest_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_deepest_2eproto
namespace config {
class Cluster;
class ClusterDefaultTypeInternal;
extern ClusterDefaultTypeInternal _Cluster_default_instance_;
class Model;
class ModelDefaultTypeInternal;
extern ModelDefaultTypeInternal _Model_default_instance_;
class Module;
class ModuleDefaultTypeInternal;
extern ModuleDefaultTypeInternal _Module_default_instance_;
}  // namespace config
namespace google {
namespace protobuf {
template<> ::config::Cluster* Arena::CreateMaybeMessage<::config::Cluster>(Arena*);
template<> ::config::Model* Arena::CreateMaybeMessage<::config::Model>(Arena*);
template<> ::config::Module* Arena::CreateMaybeMessage<::config::Module>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace config {

enum Model_ModelID {
  Model_ModelID_ENERGY = 0,
  Model_ModelID_POWER = 1,
  Model_ModelID_TIME = 2,
  Model_ModelID_Model_ModelID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Model_ModelID_Model_ModelID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Model_ModelID_IsValid(int value);
const Model_ModelID Model_ModelID_ModelID_MIN = Model_ModelID_ENERGY;
const Model_ModelID Model_ModelID_ModelID_MAX = Model_ModelID_TIME;
const int Model_ModelID_ModelID_ARRAYSIZE = Model_ModelID_ModelID_MAX + 1;

const ::google::protobuf::EnumDescriptor* Model_ModelID_descriptor();
inline const ::std::string& Model_ModelID_Name(Model_ModelID value) {
  return ::google::protobuf::internal::NameOfEnum(
    Model_ModelID_descriptor(), value);
}
inline bool Model_ModelID_Parse(
    const ::std::string& name, Model_ModelID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Model_ModelID>(
    Model_ModelID_descriptor(), name, value);
}
enum Module_ModuleID {
  Module_ModuleID_CM = 0,
  Module_ModuleID_DAM = 1,
  Module_ModuleID_ESB = 2,
  Module_ModuleID_Module_ModuleID_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Module_ModuleID_Module_ModuleID_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Module_ModuleID_IsValid(int value);
const Module_ModuleID Module_ModuleID_ModuleID_MIN = Module_ModuleID_CM;
const Module_ModuleID Module_ModuleID_ModuleID_MAX = Module_ModuleID_ESB;
const int Module_ModuleID_ModuleID_ARRAYSIZE = Module_ModuleID_ModuleID_MAX + 1;

const ::google::protobuf::EnumDescriptor* Module_ModuleID_descriptor();
inline const ::std::string& Module_ModuleID_Name(Module_ModuleID value) {
  return ::google::protobuf::internal::NameOfEnum(
    Module_ModuleID_descriptor(), value);
}
inline bool Module_ModuleID_Parse(
    const ::std::string& name, Module_ModuleID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Module_ModuleID>(
    Module_ModuleID_descriptor(), name, value);
}
// ===================================================================

class Model : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:config.Model) */ {
 public:
  Model();
  virtual ~Model();

  Model(const Model& from);

  inline Model& operator=(const Model& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Model(Model&& from) noexcept
    : Model() {
    *this = ::std::move(from);
  }

  inline Model& operator=(Model&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Model& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Model* internal_default_instance() {
    return reinterpret_cast<const Model*>(
               &_Model_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Model* other);
  friend void swap(Model& a, Model& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Model* New() const final {
    return CreateMaybeMessage<Model>(NULL);
  }

  Model* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Model>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Model& from);
  void MergeFrom(const Model& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Model* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef Model_ModelID ModelID;
  static const ModelID ENERGY =
    Model_ModelID_ENERGY;
  static const ModelID POWER =
    Model_ModelID_POWER;
  static const ModelID TIME =
    Model_ModelID_TIME;
  static inline bool ModelID_IsValid(int value) {
    return Model_ModelID_IsValid(value);
  }
  static const ModelID ModelID_MIN =
    Model_ModelID_ModelID_MIN;
  static const ModelID ModelID_MAX =
    Model_ModelID_ModelID_MAX;
  static const int ModelID_ARRAYSIZE =
    Model_ModelID_ModelID_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  ModelID_descriptor() {
    return Model_ModelID_descriptor();
  }
  static inline const ::std::string& ModelID_Name(ModelID value) {
    return Model_ModelID_Name(value);
  }
  static inline bool ModelID_Parse(const ::std::string& name,
      ModelID* value) {
    return Model_ModelID_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // string description = 3;
  void clear_description();
  static const int kDescriptionFieldNumber = 3;
  const ::std::string& description() const;
  void set_description(const ::std::string& value);
  #if LANG_CXX11
  void set_description(::std::string&& value);
  #endif
  void set_description(const char* value);
  void set_description(const char* value, size_t size);
  ::std::string* mutable_description();
  ::std::string* release_description();
  void set_allocated_description(::std::string* description);

  // string modelFile = 4;
  void clear_modelfile();
  static const int kModelFileFieldNumber = 4;
  const ::std::string& modelfile() const;
  void set_modelfile(const ::std::string& value);
  #if LANG_CXX11
  void set_modelfile(::std::string&& value);
  #endif
  void set_modelfile(const char* value);
  void set_modelfile(const char* value, size_t size);
  ::std::string* mutable_modelfile();
  ::std::string* release_modelfile();
  void set_allocated_modelfile(::std::string* modelfile);

  // .config.Model.ModelID type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::config::Model_ModelID type() const;
  void set_type(::config::Model_ModelID value);

  // int32 parameters = 2;
  void clear_parameters();
  static const int kParametersFieldNumber = 2;
  ::google::protobuf::int32 parameters() const;
  void set_parameters(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:config.Model)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr description_;
  ::google::protobuf::internal::ArenaStringPtr modelfile_;
  int type_;
  ::google::protobuf::int32 parameters_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_deepest_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Module : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:config.Module) */ {
 public:
  Module();
  virtual ~Module();

  Module(const Module& from);

  inline Module& operator=(const Module& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Module(Module&& from) noexcept
    : Module() {
    *this = ::std::move(from);
  }

  inline Module& operator=(Module&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Module& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Module* internal_default_instance() {
    return reinterpret_cast<const Module*>(
               &_Module_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Module* other);
  friend void swap(Module& a, Module& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Module* New() const final {
    return CreateMaybeMessage<Module>(NULL);
  }

  Module* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Module>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Module& from);
  void MergeFrom(const Module& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Module* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef Module_ModuleID ModuleID;
  static const ModuleID CM =
    Module_ModuleID_CM;
  static const ModuleID DAM =
    Module_ModuleID_DAM;
  static const ModuleID ESB =
    Module_ModuleID_ESB;
  static inline bool ModuleID_IsValid(int value) {
    return Module_ModuleID_IsValid(value);
  }
  static const ModuleID ModuleID_MIN =
    Module_ModuleID_ModuleID_MIN;
  static const ModuleID ModuleID_MAX =
    Module_ModuleID_ModuleID_MAX;
  static const int ModuleID_ARRAYSIZE =
    Module_ModuleID_ModuleID_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  ModuleID_descriptor() {
    return Module_ModuleID_descriptor();
  }
  static inline const ::std::string& ModuleID_Name(ModuleID value) {
    return Module_ModuleID_Name(value);
  }
  static inline bool ModuleID_Parse(const ::std::string& name,
      ModuleID* value) {
    return Module_ModuleID_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .config.Model models = 9;
  int models_size() const;
  void clear_models();
  static const int kModelsFieldNumber = 9;
  ::config::Model* mutable_models(int index);
  ::google::protobuf::RepeatedPtrField< ::config::Model >*
      mutable_models();
  const ::config::Model& models(int index) const;
  ::config::Model* add_models();
  const ::google::protobuf::RepeatedPtrField< ::config::Model >&
      models() const;

  // string name = 3;
  void clear_name();
  static const int kNameFieldNumber = 3;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // string description = 4;
  void clear_description();
  static const int kDescriptionFieldNumber = 4;
  const ::std::string& description() const;
  void set_description(const ::std::string& value);
  #if LANG_CXX11
  void set_description(::std::string&& value);
  #endif
  void set_description(const char* value);
  void set_description(const char* value, size_t size);
  ::std::string* mutable_description();
  ::std::string* release_description();
  void set_allocated_description(::std::string* description);

  // .config.Module.ModuleID id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::config::Module_ModuleID id() const;
  void set_id(::config::Module_ModuleID value);

  // int32 cores = 2;
  void clear_cores();
  static const int kCoresFieldNumber = 2;
  ::google::protobuf::int32 cores() const;
  void set_cores(::google::protobuf::int32 value);

  // double freqMin = 5;
  void clear_freqmin();
  static const int kFreqMinFieldNumber = 5;
  double freqmin() const;
  void set_freqmin(double value);

  // double freqMax = 6;
  void clear_freqmax();
  static const int kFreqMaxFieldNumber = 6;
  double freqmax() const;
  void set_freqmax(double value);

  // double freqInc = 7;
  void clear_freqinc();
  static const int kFreqIncFieldNumber = 7;
  double freqinc() const;
  void set_freqinc(double value);

  // double freqNom = 8;
  void clear_freqnom();
  static const int kFreqNomFieldNumber = 8;
  double freqnom() const;
  void set_freqnom(double value);

  // @@protoc_insertion_point(class_scope:config.Module)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::config::Model > models_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr description_;
  int id_;
  ::google::protobuf::int32 cores_;
  double freqmin_;
  double freqmax_;
  double freqinc_;
  double freqnom_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_deepest_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Cluster : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:config.Cluster) */ {
 public:
  Cluster();
  virtual ~Cluster();

  Cluster(const Cluster& from);

  inline Cluster& operator=(const Cluster& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Cluster(Cluster&& from) noexcept
    : Cluster() {
    *this = ::std::move(from);
  }

  inline Cluster& operator=(Cluster&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Cluster& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Cluster* internal_default_instance() {
    return reinterpret_cast<const Cluster*>(
               &_Cluster_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Cluster* other);
  friend void swap(Cluster& a, Cluster& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Cluster* New() const final {
    return CreateMaybeMessage<Cluster>(NULL);
  }

  Cluster* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Cluster>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Cluster& from);
  void MergeFrom(const Cluster& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Cluster* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .config.Module module = 1;
  int module_size() const;
  void clear_module();
  static const int kModuleFieldNumber = 1;
  ::config::Module* mutable_module(int index);
  ::google::protobuf::RepeatedPtrField< ::config::Module >*
      mutable_module();
  const ::config::Module& module(int index) const;
  ::config::Module* add_module();
  const ::google::protobuf::RepeatedPtrField< ::config::Module >&
      module() const;

  // @@protoc_insertion_point(class_scope:config.Cluster)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::config::Module > module_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_deepest_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Model

// .config.Model.ModelID type = 1;
inline void Model::clear_type() {
  type_ = 0;
}
inline ::config::Model_ModelID Model::type() const {
  // @@protoc_insertion_point(field_get:config.Model.type)
  return static_cast< ::config::Model_ModelID >(type_);
}
inline void Model::set_type(::config::Model_ModelID value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:config.Model.type)
}

// int32 parameters = 2;
inline void Model::clear_parameters() {
  parameters_ = 0;
}
inline ::google::protobuf::int32 Model::parameters() const {
  // @@protoc_insertion_point(field_get:config.Model.parameters)
  return parameters_;
}
inline void Model::set_parameters(::google::protobuf::int32 value) {
  
  parameters_ = value;
  // @@protoc_insertion_point(field_set:config.Model.parameters)
}

// string description = 3;
inline void Model::clear_description() {
  description_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Model::description() const {
  // @@protoc_insertion_point(field_get:config.Model.description)
  return description_.GetNoArena();
}
inline void Model::set_description(const ::std::string& value) {
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:config.Model.description)
}
#if LANG_CXX11
inline void Model::set_description(::std::string&& value) {
  
  description_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:config.Model.description)
}
#endif
inline void Model::set_description(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:config.Model.description)
}
inline void Model::set_description(const char* value, size_t size) {
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:config.Model.description)
}
inline ::std::string* Model::mutable_description() {
  
  // @@protoc_insertion_point(field_mutable:config.Model.description)
  return description_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Model::release_description() {
  // @@protoc_insertion_point(field_release:config.Model.description)
  
  return description_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Model::set_allocated_description(::std::string* description) {
  if (description != NULL) {
    
  } else {
    
  }
  description_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), description);
  // @@protoc_insertion_point(field_set_allocated:config.Model.description)
}

// string modelFile = 4;
inline void Model::clear_modelfile() {
  modelfile_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Model::modelfile() const {
  // @@protoc_insertion_point(field_get:config.Model.modelFile)
  return modelfile_.GetNoArena();
}
inline void Model::set_modelfile(const ::std::string& value) {
  
  modelfile_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:config.Model.modelFile)
}
#if LANG_CXX11
inline void Model::set_modelfile(::std::string&& value) {
  
  modelfile_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:config.Model.modelFile)
}
#endif
inline void Model::set_modelfile(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  modelfile_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:config.Model.modelFile)
}
inline void Model::set_modelfile(const char* value, size_t size) {
  
  modelfile_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:config.Model.modelFile)
}
inline ::std::string* Model::mutable_modelfile() {
  
  // @@protoc_insertion_point(field_mutable:config.Model.modelFile)
  return modelfile_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Model::release_modelfile() {
  // @@protoc_insertion_point(field_release:config.Model.modelFile)
  
  return modelfile_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Model::set_allocated_modelfile(::std::string* modelfile) {
  if (modelfile != NULL) {
    
  } else {
    
  }
  modelfile_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), modelfile);
  // @@protoc_insertion_point(field_set_allocated:config.Model.modelFile)
}

// -------------------------------------------------------------------

// Module

// .config.Module.ModuleID id = 1;
inline void Module::clear_id() {
  id_ = 0;
}
inline ::config::Module_ModuleID Module::id() const {
  // @@protoc_insertion_point(field_get:config.Module.id)
  return static_cast< ::config::Module_ModuleID >(id_);
}
inline void Module::set_id(::config::Module_ModuleID value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:config.Module.id)
}

// int32 cores = 2;
inline void Module::clear_cores() {
  cores_ = 0;
}
inline ::google::protobuf::int32 Module::cores() const {
  // @@protoc_insertion_point(field_get:config.Module.cores)
  return cores_;
}
inline void Module::set_cores(::google::protobuf::int32 value) {
  
  cores_ = value;
  // @@protoc_insertion_point(field_set:config.Module.cores)
}

// string name = 3;
inline void Module::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Module::name() const {
  // @@protoc_insertion_point(field_get:config.Module.name)
  return name_.GetNoArena();
}
inline void Module::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:config.Module.name)
}
#if LANG_CXX11
inline void Module::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:config.Module.name)
}
#endif
inline void Module::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:config.Module.name)
}
inline void Module::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:config.Module.name)
}
inline ::std::string* Module::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:config.Module.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Module::release_name() {
  // @@protoc_insertion_point(field_release:config.Module.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Module::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:config.Module.name)
}

// string description = 4;
inline void Module::clear_description() {
  description_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Module::description() const {
  // @@protoc_insertion_point(field_get:config.Module.description)
  return description_.GetNoArena();
}
inline void Module::set_description(const ::std::string& value) {
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:config.Module.description)
}
#if LANG_CXX11
inline void Module::set_description(::std::string&& value) {
  
  description_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:config.Module.description)
}
#endif
inline void Module::set_description(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:config.Module.description)
}
inline void Module::set_description(const char* value, size_t size) {
  
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:config.Module.description)
}
inline ::std::string* Module::mutable_description() {
  
  // @@protoc_insertion_point(field_mutable:config.Module.description)
  return description_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Module::release_description() {
  // @@protoc_insertion_point(field_release:config.Module.description)
  
  return description_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Module::set_allocated_description(::std::string* description) {
  if (description != NULL) {
    
  } else {
    
  }
  description_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), description);
  // @@protoc_insertion_point(field_set_allocated:config.Module.description)
}

// double freqMin = 5;
inline void Module::clear_freqmin() {
  freqmin_ = 0;
}
inline double Module::freqmin() const {
  // @@protoc_insertion_point(field_get:config.Module.freqMin)
  return freqmin_;
}
inline void Module::set_freqmin(double value) {
  
  freqmin_ = value;
  // @@protoc_insertion_point(field_set:config.Module.freqMin)
}

// double freqMax = 6;
inline void Module::clear_freqmax() {
  freqmax_ = 0;
}
inline double Module::freqmax() const {
  // @@protoc_insertion_point(field_get:config.Module.freqMax)
  return freqmax_;
}
inline void Module::set_freqmax(double value) {
  
  freqmax_ = value;
  // @@protoc_insertion_point(field_set:config.Module.freqMax)
}

// double freqInc = 7;
inline void Module::clear_freqinc() {
  freqinc_ = 0;
}
inline double Module::freqinc() const {
  // @@protoc_insertion_point(field_get:config.Module.freqInc)
  return freqinc_;
}
inline void Module::set_freqinc(double value) {
  
  freqinc_ = value;
  // @@protoc_insertion_point(field_set:config.Module.freqInc)
}

// double freqNom = 8;
inline void Module::clear_freqnom() {
  freqnom_ = 0;
}
inline double Module::freqnom() const {
  // @@protoc_insertion_point(field_get:config.Module.freqNom)
  return freqnom_;
}
inline void Module::set_freqnom(double value) {
  
  freqnom_ = value;
  // @@protoc_insertion_point(field_set:config.Module.freqNom)
}

// repeated .config.Model models = 9;
inline int Module::models_size() const {
  return models_.size();
}
inline void Module::clear_models() {
  models_.Clear();
}
inline ::config::Model* Module::mutable_models(int index) {
  // @@protoc_insertion_point(field_mutable:config.Module.models)
  return models_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::config::Model >*
Module::mutable_models() {
  // @@protoc_insertion_point(field_mutable_list:config.Module.models)
  return &models_;
}
inline const ::config::Model& Module::models(int index) const {
  // @@protoc_insertion_point(field_get:config.Module.models)
  return models_.Get(index);
}
inline ::config::Model* Module::add_models() {
  // @@protoc_insertion_point(field_add:config.Module.models)
  return models_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::config::Model >&
Module::models() const {
  // @@protoc_insertion_point(field_list:config.Module.models)
  return models_;
}

// -------------------------------------------------------------------

// Cluster

// repeated .config.Module module = 1;
inline int Cluster::module_size() const {
  return module_.size();
}
inline void Cluster::clear_module() {
  module_.Clear();
}
inline ::config::Module* Cluster::mutable_module(int index) {
  // @@protoc_insertion_point(field_mutable:config.Cluster.module)
  return module_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::config::Module >*
Cluster::mutable_module() {
  // @@protoc_insertion_point(field_mutable_list:config.Cluster.module)
  return &module_;
}
inline const ::config::Module& Cluster::module(int index) const {
  // @@protoc_insertion_point(field_get:config.Cluster.module)
  return module_.Get(index);
}
inline ::config::Module* Cluster::add_module() {
  // @@protoc_insertion_point(field_add:config.Cluster.module)
  return module_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::config::Module >&
Cluster::module() const {
  // @@protoc_insertion_point(field_list:config.Cluster.module)
  return module_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace config

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::config::Model_ModelID> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::config::Model_ModelID>() {
  return ::config::Model_ModelID_descriptor();
}
template <> struct is_proto_enum< ::config::Module_ModuleID> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::config::Module_ModuleID>() {
  return ::config::Module_ModuleID_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_deepest_2eproto
