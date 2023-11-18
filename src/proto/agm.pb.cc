// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/agm.proto

#include "proto/agm.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;

inline constexpr TileType::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : uuid_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        title_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        graphicindex_{0},
        solid_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR TileType::TileType(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct TileTypeDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TileTypeDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TileTypeDefaultTypeInternal() {}
  union {
    TileType _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TileTypeDefaultTypeInternal _TileType_default_instance_;

inline constexpr MapLayer::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : tiles_{},
        _tiles_cached_byte_size_{0},
        uuid_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        width_{0},
        height_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR MapLayer::MapLayer(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct MapLayerDefaultTypeInternal {
  PROTOBUF_CONSTEXPR MapLayerDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~MapLayerDefaultTypeInternal() {}
  union {
    MapLayer _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 MapLayerDefaultTypeInternal _MapLayer_default_instance_;

inline constexpr AGM::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : tiletypes_{},
        layers_{},
        title_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        width_{0},
        height_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR AGM::AGM(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct AGMDefaultTypeInternal {
  PROTOBUF_CONSTEXPR AGMDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~AGMDefaultTypeInternal() {}
  union {
    AGM _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 AGMDefaultTypeInternal _AGM_default_instance_;
static ::_pb::Metadata file_level_metadata_proto_2fagm_2eproto[3];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_proto_2fagm_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_proto_2fagm_2eproto = nullptr;
const ::uint32_t TableStruct_proto_2fagm_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::TileType, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::TileType, _impl_.uuid_),
    PROTOBUF_FIELD_OFFSET(::TileType, _impl_.title_),
    PROTOBUF_FIELD_OFFSET(::TileType, _impl_.graphicindex_),
    PROTOBUF_FIELD_OFFSET(::TileType, _impl_.solid_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::MapLayer, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::MapLayer, _impl_.uuid_),
    PROTOBUF_FIELD_OFFSET(::MapLayer, _impl_.width_),
    PROTOBUF_FIELD_OFFSET(::MapLayer, _impl_.height_),
    PROTOBUF_FIELD_OFFSET(::MapLayer, _impl_.tiles_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::AGM, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::AGM, _impl_.title_),
    PROTOBUF_FIELD_OFFSET(::AGM, _impl_.tiletypes_),
    PROTOBUF_FIELD_OFFSET(::AGM, _impl_.width_),
    PROTOBUF_FIELD_OFFSET(::AGM, _impl_.height_),
    PROTOBUF_FIELD_OFFSET(::AGM, _impl_.layers_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::TileType)},
        {12, -1, -1, sizeof(::MapLayer)},
        {24, -1, -1, sizeof(::AGM)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::_TileType_default_instance_._instance,
    &::_MapLayer_default_instance_._instance,
    &::_AGM_default_instance_._instance,
};
const char descriptor_table_protodef_proto_2fagm_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\017proto/agm.proto\"L\n\010TileType\022\014\n\004uuid\030\001 "
    "\001(\t\022\r\n\005title\030\002 \001(\t\022\024\n\014graphicIndex\030\003 \001(\005"
    "\022\r\n\005solid\030\004 \001(\010\"F\n\010MapLayer\022\014\n\004uuid\030\001 \001("
    "\t\022\r\n\005width\030\002 \001(\005\022\016\n\006height\030\003 \001(\005\022\r\n\005tile"
    "s\030\004 \003(\005\"l\n\003AGM\022\r\n\005title\030\001 \001(\t\022\034\n\ttileTyp"
    "es\030\002 \003(\0132\t.TileType\022\r\n\005width\030\003 \001(\005\022\016\n\006he"
    "ight\030\004 \001(\005\022\031\n\006layers\030\005 \003(\0132\t.MapLayerb\006p"
    "roto3"
};
static ::absl::once_flag descriptor_table_proto_2fagm_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_proto_2fagm_2eproto = {
    false,
    false,
    285,
    descriptor_table_protodef_proto_2fagm_2eproto,
    "proto/agm.proto",
    &descriptor_table_proto_2fagm_2eproto_once,
    nullptr,
    0,
    3,
    schemas,
    file_default_instances,
    TableStruct_proto_2fagm_2eproto::offsets,
    file_level_metadata_proto_2fagm_2eproto,
    file_level_enum_descriptors_proto_2fagm_2eproto,
    file_level_service_descriptors_proto_2fagm_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_proto_2fagm_2eproto_getter() {
  return &descriptor_table_proto_2fagm_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_proto_2fagm_2eproto(&descriptor_table_proto_2fagm_2eproto);
// ===================================================================

class TileType::_Internal {
 public:
};

TileType::TileType(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:TileType)
}
inline PROTOBUF_NDEBUG_INLINE TileType::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : uuid_(arena, from.uuid_),
        title_(arena, from.title_),
        _cached_size_{0} {}

TileType::TileType(
    ::google::protobuf::Arena* arena,
    const TileType& from)
    : ::google::protobuf::Message(arena) {
  TileType* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, graphicindex_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, graphicindex_),
           offsetof(Impl_, solid_) -
               offsetof(Impl_, graphicindex_) +
               sizeof(Impl_::solid_));

  // @@protoc_insertion_point(copy_constructor:TileType)
}
inline PROTOBUF_NDEBUG_INLINE TileType::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : uuid_(arena),
        title_(arena),
        _cached_size_{0} {}

inline void TileType::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, graphicindex_),
           0,
           offsetof(Impl_, solid_) -
               offsetof(Impl_, graphicindex_) +
               sizeof(Impl_::solid_));
}
TileType::~TileType() {
  // @@protoc_insertion_point(destructor:TileType)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void TileType::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.uuid_.Destroy();
  _impl_.title_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void TileType::Clear() {
// @@protoc_insertion_point(message_clear_start:TileType)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.uuid_.ClearToEmpty();
  _impl_.title_.ClearToEmpty();
  ::memset(&_impl_.graphicindex_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.solid_) -
      reinterpret_cast<char*>(&_impl_.graphicindex_)) + sizeof(_impl_.solid_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* TileType::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 26, 2> TileType::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_TileType_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // bool solid = 4;
    {::_pbi::TcParser::SingularVarintNoZag1<bool, offsetof(TileType, _impl_.solid_), 63>(),
     {32, 63, 0, PROTOBUF_FIELD_OFFSET(TileType, _impl_.solid_)}},
    // string uuid = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(TileType, _impl_.uuid_)}},
    // string title = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(TileType, _impl_.title_)}},
    // int32 graphicIndex = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(TileType, _impl_.graphicindex_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(TileType, _impl_.graphicindex_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string uuid = 1;
    {PROTOBUF_FIELD_OFFSET(TileType, _impl_.uuid_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string title = 2;
    {PROTOBUF_FIELD_OFFSET(TileType, _impl_.title_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // int32 graphicIndex = 3;
    {PROTOBUF_FIELD_OFFSET(TileType, _impl_.graphicindex_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // bool solid = 4;
    {PROTOBUF_FIELD_OFFSET(TileType, _impl_.solid_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
  }},
  // no aux_entries
  {{
    "\10\4\5\0\0\0\0\0"
    "TileType"
    "uuid"
    "title"
  }},
};

::uint8_t* TileType::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:TileType)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    const std::string& _s = this->_internal_uuid();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "TileType.uuid");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // string title = 2;
  if (!this->_internal_title().empty()) {
    const std::string& _s = this->_internal_title();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "TileType.title");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // int32 graphicIndex = 3;
  if (this->_internal_graphicindex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_graphicindex(), target);
  }

  // bool solid = 4;
  if (this->_internal_solid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(
        4, this->_internal_solid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:TileType)
  return target;
}

::size_t TileType::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:TileType)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_uuid());
  }

  // string title = 2;
  if (!this->_internal_title().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_title());
  }

  // int32 graphicIndex = 3;
  if (this->_internal_graphicindex() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_graphicindex());
  }

  // bool solid = 4;
  if (this->_internal_solid() != 0) {
    total_size += 2;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData TileType::_class_data_ = {
    TileType::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* TileType::GetClassData() const {
  return &_class_data_;
}

void TileType::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<TileType*>(&to_msg);
  auto& from = static_cast<const TileType&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:TileType)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_uuid().empty()) {
    _this->_internal_set_uuid(from._internal_uuid());
  }
  if (!from._internal_title().empty()) {
    _this->_internal_set_title(from._internal_title());
  }
  if (from._internal_graphicindex() != 0) {
    _this->_internal_set_graphicindex(from._internal_graphicindex());
  }
  if (from._internal_solid() != 0) {
    _this->_internal_set_solid(from._internal_solid());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void TileType::CopyFrom(const TileType& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:TileType)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool TileType::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* TileType::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void TileType::InternalSwap(TileType* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.uuid_, &other->_impl_.uuid_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.title_, &other->_impl_.title_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TileType, _impl_.solid_)
      + sizeof(TileType::_impl_.solid_)
      - PROTOBUF_FIELD_OFFSET(TileType, _impl_.graphicindex_)>(
          reinterpret_cast<char*>(&_impl_.graphicindex_),
          reinterpret_cast<char*>(&other->_impl_.graphicindex_));
}

::google::protobuf::Metadata TileType::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_proto_2fagm_2eproto_getter, &descriptor_table_proto_2fagm_2eproto_once,
      file_level_metadata_proto_2fagm_2eproto[0]);
}
// ===================================================================

class MapLayer::_Internal {
 public:
};

MapLayer::MapLayer(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:MapLayer)
}
inline PROTOBUF_NDEBUG_INLINE MapLayer::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : tiles_{visibility, arena, from.tiles_},
        _tiles_cached_byte_size_{0},
        uuid_(arena, from.uuid_),
        _cached_size_{0} {}

MapLayer::MapLayer(
    ::google::protobuf::Arena* arena,
    const MapLayer& from)
    : ::google::protobuf::Message(arena) {
  MapLayer* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, width_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, width_),
           offsetof(Impl_, height_) -
               offsetof(Impl_, width_) +
               sizeof(Impl_::height_));

  // @@protoc_insertion_point(copy_constructor:MapLayer)
}
inline PROTOBUF_NDEBUG_INLINE MapLayer::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : tiles_{visibility, arena},
        _tiles_cached_byte_size_{0},
        uuid_(arena),
        _cached_size_{0} {}

inline void MapLayer::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, width_),
           0,
           offsetof(Impl_, height_) -
               offsetof(Impl_, width_) +
               sizeof(Impl_::height_));
}
MapLayer::~MapLayer() {
  // @@protoc_insertion_point(destructor:MapLayer)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void MapLayer::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.uuid_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void MapLayer::Clear() {
// @@protoc_insertion_point(message_clear_start:MapLayer)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.tiles_.Clear();
  _impl_.uuid_.ClearToEmpty();
  ::memset(&_impl_.width_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.height_) -
      reinterpret_cast<char*>(&_impl_.width_)) + sizeof(_impl_.height_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* MapLayer::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 21, 2> MapLayer::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_MapLayer_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // repeated int32 tiles = 4;
    {::_pbi::TcParser::FastV32P1,
     {34, 63, 0, PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.tiles_)}},
    // string uuid = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.uuid_)}},
    // int32 width = 2;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(MapLayer, _impl_.width_), 63>(),
     {16, 63, 0, PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.width_)}},
    // int32 height = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(MapLayer, _impl_.height_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.height_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string uuid = 1;
    {PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.uuid_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // int32 width = 2;
    {PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.width_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // int32 height = 3;
    {PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.height_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // repeated int32 tiles = 4;
    {PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.tiles_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kPackedInt32)},
  }},
  // no aux_entries
  {{
    "\10\4\0\0\0\0\0\0"
    "MapLayer"
    "uuid"
  }},
};

::uint8_t* MapLayer::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:MapLayer)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    const std::string& _s = this->_internal_uuid();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "MapLayer.uuid");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // int32 width = 2;
  if (this->_internal_width() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<2>(
            stream, this->_internal_width(), target);
  }

  // int32 height = 3;
  if (this->_internal_height() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_height(), target);
  }

  // repeated int32 tiles = 4;
  {
    int byte_size = _impl_._tiles_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          4, _internal_tiles(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MapLayer)
  return target;
}

::size_t MapLayer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MapLayer)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 tiles = 4;
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal_tiles())
    ;
    _impl_._tiles_cached_byte_size_.Set(::_pbi::ToCachedSize(data_size));
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }
  // string uuid = 1;
  if (!this->_internal_uuid().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_uuid());
  }

  // int32 width = 2;
  if (this->_internal_width() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_width());
  }

  // int32 height = 3;
  if (this->_internal_height() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_height());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData MapLayer::_class_data_ = {
    MapLayer::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* MapLayer::GetClassData() const {
  return &_class_data_;
}

void MapLayer::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<MapLayer*>(&to_msg);
  auto& from = static_cast<const MapLayer&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:MapLayer)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_tiles()->MergeFrom(from._internal_tiles());
  if (!from._internal_uuid().empty()) {
    _this->_internal_set_uuid(from._internal_uuid());
  }
  if (from._internal_width() != 0) {
    _this->_internal_set_width(from._internal_width());
  }
  if (from._internal_height() != 0) {
    _this->_internal_set_height(from._internal_height());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void MapLayer::CopyFrom(const MapLayer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MapLayer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool MapLayer::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* MapLayer::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void MapLayer::InternalSwap(MapLayer* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.tiles_.InternalSwap(&other->_impl_.tiles_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.uuid_, &other->_impl_.uuid_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.height_)
      + sizeof(MapLayer::_impl_.height_)
      - PROTOBUF_FIELD_OFFSET(MapLayer, _impl_.width_)>(
          reinterpret_cast<char*>(&_impl_.width_),
          reinterpret_cast<char*>(&other->_impl_.width_));
}

::google::protobuf::Metadata MapLayer::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_proto_2fagm_2eproto_getter, &descriptor_table_proto_2fagm_2eproto_once,
      file_level_metadata_proto_2fagm_2eproto[1]);
}
// ===================================================================

class AGM::_Internal {
 public:
};

AGM::AGM(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:AGM)
}
inline PROTOBUF_NDEBUG_INLINE AGM::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : tiletypes_{visibility, arena, from.tiletypes_},
        layers_{visibility, arena, from.layers_},
        title_(arena, from.title_),
        _cached_size_{0} {}

AGM::AGM(
    ::google::protobuf::Arena* arena,
    const AGM& from)
    : ::google::protobuf::Message(arena) {
  AGM* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, width_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, width_),
           offsetof(Impl_, height_) -
               offsetof(Impl_, width_) +
               sizeof(Impl_::height_));

  // @@protoc_insertion_point(copy_constructor:AGM)
}
inline PROTOBUF_NDEBUG_INLINE AGM::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : tiletypes_{visibility, arena},
        layers_{visibility, arena},
        title_(arena),
        _cached_size_{0} {}

inline void AGM::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, width_),
           0,
           offsetof(Impl_, height_) -
               offsetof(Impl_, width_) +
               sizeof(Impl_::height_));
}
AGM::~AGM() {
  // @@protoc_insertion_point(destructor:AGM)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void AGM::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.title_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void AGM::Clear() {
// @@protoc_insertion_point(message_clear_start:AGM)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.tiletypes_.Clear();
  _impl_.layers_.Clear();
  _impl_.title_.ClearToEmpty();
  ::memset(&_impl_.width_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.height_) -
      reinterpret_cast<char*>(&_impl_.width_)) + sizeof(_impl_.height_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* AGM::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<3, 5, 2, 17, 2> AGM::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    5, 56,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967264,  // skipmap
    offsetof(decltype(_table_), field_entries),
    5,  // num_field_entries
    2,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_AGM_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // string title = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(AGM, _impl_.title_)}},
    // repeated .TileType tileTypes = 2;
    {::_pbi::TcParser::FastMtR1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(AGM, _impl_.tiletypes_)}},
    // int32 width = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(AGM, _impl_.width_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(AGM, _impl_.width_)}},
    // int32 height = 4;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(AGM, _impl_.height_), 63>(),
     {32, 63, 0, PROTOBUF_FIELD_OFFSET(AGM, _impl_.height_)}},
    // repeated .MapLayer layers = 5;
    {::_pbi::TcParser::FastMtR1,
     {42, 63, 1, PROTOBUF_FIELD_OFFSET(AGM, _impl_.layers_)}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // string title = 1;
    {PROTOBUF_FIELD_OFFSET(AGM, _impl_.title_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // repeated .TileType tileTypes = 2;
    {PROTOBUF_FIELD_OFFSET(AGM, _impl_.tiletypes_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kMessage | ::_fl::kTvTable)},
    // int32 width = 3;
    {PROTOBUF_FIELD_OFFSET(AGM, _impl_.width_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // int32 height = 4;
    {PROTOBUF_FIELD_OFFSET(AGM, _impl_.height_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // repeated .MapLayer layers = 5;
    {PROTOBUF_FIELD_OFFSET(AGM, _impl_.layers_), 0, 1,
    (0 | ::_fl::kFcRepeated | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::TileType>()},
    {::_pbi::TcParser::GetTable<::MapLayer>()},
  }}, {{
    "\3\5\0\0\0\0\0\0"
    "AGM"
    "title"
  }},
};

::uint8_t* AGM::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:AGM)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string title = 1;
  if (!this->_internal_title().empty()) {
    const std::string& _s = this->_internal_title();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "AGM.title");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // repeated .TileType tileTypes = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_tiletypes_size()); i < n; i++) {
    const auto& repfield = this->_internal_tiletypes().Get(i);
    target = ::google::protobuf::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  // int32 width = 3;
  if (this->_internal_width() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_width(), target);
  }

  // int32 height = 4;
  if (this->_internal_height() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<4>(
            stream, this->_internal_height(), target);
  }

  // repeated .MapLayer layers = 5;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_layers_size()); i < n; i++) {
    const auto& repfield = this->_internal_layers().Get(i);
    target = ::google::protobuf::internal::WireFormatLite::
        InternalWriteMessage(5, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AGM)
  return target;
}

::size_t AGM::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:AGM)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .TileType tileTypes = 2;
  total_size += 1UL * this->_internal_tiletypes_size();
  for (const auto& msg : this->_internal_tiletypes()) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSize(msg);
  }
  // repeated .MapLayer layers = 5;
  total_size += 1UL * this->_internal_layers_size();
  for (const auto& msg : this->_internal_layers()) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSize(msg);
  }
  // string title = 1;
  if (!this->_internal_title().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_title());
  }

  // int32 width = 3;
  if (this->_internal_width() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_width());
  }

  // int32 height = 4;
  if (this->_internal_height() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_height());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData AGM::_class_data_ = {
    AGM::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* AGM::GetClassData() const {
  return &_class_data_;
}

void AGM::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<AGM*>(&to_msg);
  auto& from = static_cast<const AGM&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:AGM)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_tiletypes()->MergeFrom(
      from._internal_tiletypes());
  _this->_internal_mutable_layers()->MergeFrom(
      from._internal_layers());
  if (!from._internal_title().empty()) {
    _this->_internal_set_title(from._internal_title());
  }
  if (from._internal_width() != 0) {
    _this->_internal_set_width(from._internal_width());
  }
  if (from._internal_height() != 0) {
    _this->_internal_set_height(from._internal_height());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void AGM::CopyFrom(const AGM& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:AGM)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool AGM::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* AGM::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void AGM::InternalSwap(AGM* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.tiletypes_.InternalSwap(&other->_impl_.tiletypes_);
  _impl_.layers_.InternalSwap(&other->_impl_.layers_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.title_, &other->_impl_.title_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(AGM, _impl_.height_)
      + sizeof(AGM::_impl_.height_)
      - PROTOBUF_FIELD_OFFSET(AGM, _impl_.width_)>(
          reinterpret_cast<char*>(&_impl_.width_),
          reinterpret_cast<char*>(&other->_impl_.width_));
}

::google::protobuf::Metadata AGM::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_proto_2fagm_2eproto_getter, &descriptor_table_proto_2fagm_2eproto_once,
      file_level_metadata_proto_2fagm_2eproto[2]);
}
// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
