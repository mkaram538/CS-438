// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: coord.proto

#include "coord.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace csce438 {
constexpr ClientInfo::ClientInfo(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : id_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct ClientInfoDefaultTypeInternal {
  constexpr ClientInfoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ClientInfoDefaultTypeInternal() {}
  union {
    ClientInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ClientInfoDefaultTypeInternal _ClientInfo_default_instance_;
constexpr SyncerInfo::SyncerInfo(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : port_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct SyncerInfoDefaultTypeInternal {
  constexpr SyncerInfoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~SyncerInfoDefaultTypeInternal() {}
  union {
    SyncerInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT SyncerInfoDefaultTypeInternal _SyncerInfo_default_instance_;
constexpr None::None(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized){}
struct NoneDefaultTypeInternal {
  constexpr NoneDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~NoneDefaultTypeInternal() {}
  union {
    None _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT NoneDefaultTypeInternal _None_default_instance_;
constexpr ServerInfo::ServerInfo(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : port_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , type_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , id_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct ServerInfoDefaultTypeInternal {
  constexpr ServerInfoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ServerInfoDefaultTypeInternal() {}
  union {
    ServerInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ServerInfoDefaultTypeInternal _ServerInfo_default_instance_;
}  // namespace csce438
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_coord_2eproto[4];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_coord_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_coord_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_coord_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::csce438::ClientInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::csce438::ClientInfo, id_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::csce438::SyncerInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::csce438::SyncerInfo, port_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::csce438::None, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::csce438::ServerInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::csce438::ServerInfo, port_),
  PROTOBUF_FIELD_OFFSET(::csce438::ServerInfo, type_),
  PROTOBUF_FIELD_OFFSET(::csce438::ServerInfo, id_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::csce438::ClientInfo)},
  { 7, -1, -1, sizeof(::csce438::SyncerInfo)},
  { 14, -1, -1, sizeof(::csce438::None)},
  { 20, -1, -1, sizeof(::csce438::ServerInfo)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::csce438::_ClientInfo_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::csce438::_SyncerInfo_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::csce438::_None_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::csce438::_ServerInfo_default_instance_),
};

const char descriptor_table_protodef_coord_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013coord.proto\022\007csce438\032\037google/protobuf/"
  "timestamp.proto\"\030\n\nClientInfo\022\n\n\002id\030\001 \001("
  "\t\"\032\n\nSyncerInfo\022\014\n\004port\030\001 \001(\t\"\006\n\004None\"4\n"
  "\nServerInfo\022\014\n\004port\030\001 \001(\t\022\014\n\004type\030\002 \001(\t\022"
  "\n\n\002id\030\003 \001(\t2\250\002\n\014COORDService\0227\n\tGetServe"
  "r\022\023.csce438.ClientInfo\032\023.csce438.ServerI"
  "nfo\"\000\0226\n\010GetSlave\022\023.csce438.ClientInfo\032\023"
  ".csce438.ServerInfo\"\000\022=\n\017GetFollowSyncer"
  "\022\023.csce438.ClientInfo\032\023.csce438.SyncerIn"
  "fo\"\000\0229\n\013BeginServer\022\023.csce438.ServerInfo"
  "\032\023.csce438.ServerInfo\"\000\022-\n\005Pulse\022\023.csce4"
  "38.ServerInfo\032\r.csce438.None\"\000b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_coord_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2ftimestamp_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_coord_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_coord_2eproto = {
  false, false, 478, descriptor_table_protodef_coord_2eproto, "coord.proto", 
  &descriptor_table_coord_2eproto_once, descriptor_table_coord_2eproto_deps, 1, 4,
  schemas, file_default_instances, TableStruct_coord_2eproto::offsets,
  file_level_metadata_coord_2eproto, file_level_enum_descriptors_coord_2eproto, file_level_service_descriptors_coord_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_coord_2eproto_getter() {
  return &descriptor_table_coord_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_coord_2eproto(&descriptor_table_coord_2eproto);
namespace csce438 {

// ===================================================================

class ClientInfo::_Internal {
 public:
};

ClientInfo::ClientInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:csce438.ClientInfo)
}
ClientInfo::ClientInfo(const ClientInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_id().empty()) {
    id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_id(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:csce438.ClientInfo)
}

void ClientInfo::SharedCtor() {
id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

ClientInfo::~ClientInfo() {
  // @@protoc_insertion_point(destructor:csce438.ClientInfo)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ClientInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ClientInfo::ArenaDtor(void* object) {
  ClientInfo* _this = reinterpret_cast< ClientInfo* >(object);
  (void)_this;
}
void ClientInfo::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ClientInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ClientInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:csce438.ClientInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ClientInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_id();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "csce438.ClientInfo.id"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ClientInfo::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:csce438.ClientInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_id().data(), static_cast<int>(this->_internal_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "csce438.ClientInfo.id");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:csce438.ClientInfo)
  return target;
}

size_t ClientInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:csce438.ClientInfo)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ClientInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ClientInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ClientInfo::GetClassData() const { return &_class_data_; }

void ClientInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ClientInfo *>(to)->MergeFrom(
      static_cast<const ClientInfo &>(from));
}


void ClientInfo::MergeFrom(const ClientInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:csce438.ClientInfo)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_id().empty()) {
    _internal_set_id(from._internal_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ClientInfo::CopyFrom(const ClientInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:csce438.ClientInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClientInfo::IsInitialized() const {
  return true;
}

void ClientInfo::InternalSwap(ClientInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &id_, lhs_arena,
      &other->id_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata ClientInfo::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_coord_2eproto_getter, &descriptor_table_coord_2eproto_once,
      file_level_metadata_coord_2eproto[0]);
}

// ===================================================================

class SyncerInfo::_Internal {
 public:
};

SyncerInfo::SyncerInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:csce438.SyncerInfo)
}
SyncerInfo::SyncerInfo(const SyncerInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  port_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_port().empty()) {
    port_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_port(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:csce438.SyncerInfo)
}

void SyncerInfo::SharedCtor() {
port_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

SyncerInfo::~SyncerInfo() {
  // @@protoc_insertion_point(destructor:csce438.SyncerInfo)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void SyncerInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  port_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void SyncerInfo::ArenaDtor(void* object) {
  SyncerInfo* _this = reinterpret_cast< SyncerInfo* >(object);
  (void)_this;
}
void SyncerInfo::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void SyncerInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void SyncerInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:csce438.SyncerInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  port_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SyncerInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string port = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_port();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "csce438.SyncerInfo.port"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* SyncerInfo::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:csce438.SyncerInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string port = 1;
  if (!this->_internal_port().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_port().data(), static_cast<int>(this->_internal_port().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "csce438.SyncerInfo.port");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_port(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:csce438.SyncerInfo)
  return target;
}

size_t SyncerInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:csce438.SyncerInfo)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string port = 1;
  if (!this->_internal_port().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_port());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SyncerInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    SyncerInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SyncerInfo::GetClassData() const { return &_class_data_; }

void SyncerInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<SyncerInfo *>(to)->MergeFrom(
      static_cast<const SyncerInfo &>(from));
}


void SyncerInfo::MergeFrom(const SyncerInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:csce438.SyncerInfo)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_port().empty()) {
    _internal_set_port(from._internal_port());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SyncerInfo::CopyFrom(const SyncerInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:csce438.SyncerInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SyncerInfo::IsInitialized() const {
  return true;
}

void SyncerInfo::InternalSwap(SyncerInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &port_, lhs_arena,
      &other->port_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata SyncerInfo::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_coord_2eproto_getter, &descriptor_table_coord_2eproto_once,
      file_level_metadata_coord_2eproto[1]);
}

// ===================================================================

class None::_Internal {
 public:
};

None::None(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena, is_message_owned) {
  // @@protoc_insertion_point(arena_constructor:csce438.None)
}
None::None(const None& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:csce438.None)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData None::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*None::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata None::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_coord_2eproto_getter, &descriptor_table_coord_2eproto_once,
      file_level_metadata_coord_2eproto[2]);
}

// ===================================================================

class ServerInfo::_Internal {
 public:
};

ServerInfo::ServerInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:csce438.ServerInfo)
}
ServerInfo::ServerInfo(const ServerInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  port_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_port().empty()) {
    port_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_port(), 
      GetArenaForAllocation());
  }
  type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_type().empty()) {
    type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_type(), 
      GetArenaForAllocation());
  }
  id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_id().empty()) {
    id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_id(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:csce438.ServerInfo)
}

void ServerInfo::SharedCtor() {
port_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

ServerInfo::~ServerInfo() {
  // @@protoc_insertion_point(destructor:csce438.ServerInfo)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ServerInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  port_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  type_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ServerInfo::ArenaDtor(void* object) {
  ServerInfo* _this = reinterpret_cast< ServerInfo* >(object);
  (void)_this;
}
void ServerInfo::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ServerInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ServerInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:csce438.ServerInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  port_.ClearToEmpty();
  type_.ClearToEmpty();
  id_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ServerInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string port = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_port();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "csce438.ServerInfo.port"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_type();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "csce438.ServerInfo.type"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_id();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "csce438.ServerInfo.id"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ServerInfo::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:csce438.ServerInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string port = 1;
  if (!this->_internal_port().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_port().data(), static_cast<int>(this->_internal_port().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "csce438.ServerInfo.port");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_port(), target);
  }

  // string type = 2;
  if (!this->_internal_type().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_type().data(), static_cast<int>(this->_internal_type().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "csce438.ServerInfo.type");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_type(), target);
  }

  // string id = 3;
  if (!this->_internal_id().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_id().data(), static_cast<int>(this->_internal_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "csce438.ServerInfo.id");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:csce438.ServerInfo)
  return target;
}

size_t ServerInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:csce438.ServerInfo)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string port = 1;
  if (!this->_internal_port().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_port());
  }

  // string type = 2;
  if (!this->_internal_type().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_type());
  }

  // string id = 3;
  if (!this->_internal_id().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ServerInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ServerInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ServerInfo::GetClassData() const { return &_class_data_; }

void ServerInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ServerInfo *>(to)->MergeFrom(
      static_cast<const ServerInfo &>(from));
}


void ServerInfo::MergeFrom(const ServerInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:csce438.ServerInfo)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_port().empty()) {
    _internal_set_port(from._internal_port());
  }
  if (!from._internal_type().empty()) {
    _internal_set_type(from._internal_type());
  }
  if (!from._internal_id().empty()) {
    _internal_set_id(from._internal_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ServerInfo::CopyFrom(const ServerInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:csce438.ServerInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServerInfo::IsInitialized() const {
  return true;
}

void ServerInfo::InternalSwap(ServerInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &port_, lhs_arena,
      &other->port_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &type_, lhs_arena,
      &other->type_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &id_, lhs_arena,
      &other->id_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata ServerInfo::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_coord_2eproto_getter, &descriptor_table_coord_2eproto_once,
      file_level_metadata_coord_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace csce438
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::csce438::ClientInfo* Arena::CreateMaybeMessage< ::csce438::ClientInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::csce438::ClientInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::csce438::SyncerInfo* Arena::CreateMaybeMessage< ::csce438::SyncerInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::csce438::SyncerInfo >(arena);
}
template<> PROTOBUF_NOINLINE ::csce438::None* Arena::CreateMaybeMessage< ::csce438::None >(Arena* arena) {
  return Arena::CreateMessageInternal< ::csce438::None >(arena);
}
template<> PROTOBUF_NOINLINE ::csce438::ServerInfo* Arena::CreateMaybeMessage< ::csce438::ServerInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::csce438::ServerInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
