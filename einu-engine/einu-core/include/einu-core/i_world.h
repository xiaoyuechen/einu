#pragma once

#include <memory>

#include "einu-core/entity_buffer.h"
#include "einu-core/i_entity.h"
#include "einu-core/internal/xnent_mask.h"
#include "einu-core/need_list.h"

namespace einu {

class IWorld {
 public:
  void AddEntity(IEntity& ett) { AddEntityImpl(ett); }
  void RemoveEntity(EID eid) noexcept { RemoveEntityImpl(eid); }
  IEntity& GetEntity(EID eid) noexcept { return GetEntityImpl(eid); }
  const IEntity& GetEntity(EID eid) const noexcept {
    return GetEntityImpl(eid);
  }
  std::size_t GetEntityCount() const noexcept { return GetEntityCountImpl(); }
  void GetAllEntities(EntityBuffer& buffer) const {
    return GetAllEntitiesImpl(buffer);
  }

  template <typename SinglenentList>
  bool HasSinglenents(
      SinglenentList l,
      const internal::DynamicXnentMask& mask =
          internal::GetXnentMask(SinglenentList{})) const noexcept {
    return HasSinglenentsImpl(mask);
  }

  template <typename Singlenent>
  void AddSinglenent(Singlenent& singlenent,
                     internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) {
    AddSinglenentImpl(id, singlenent);
  }

  template <typename Singlenent>
  Singlenent& RemoveSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) noexcept {
    return RemoveSinglenentImpl(id);
  }

  template <typename Singlenent>
  const Singlenent& GetSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) const noexcept {
    return GetSinglenentImpl(id);
  }

  template <typename Singlenent>
  Singlenent& GetSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) noexcept {
    return GetSinglenentImpl(id);
  }

 protected:
  virtual void AddEntityImpl(IEntity& ett) = 0;
  virtual void RemoveEntityImpl(EID eid) noexcept = 0;
  virtual IEntity& GetEntityImpl(EID eid) noexcept = 0;
  virtual const IEntity& GetEntityImpl(EID eid) const noexcept = 0;
  virtual std::size_t GetEntityCountImpl() const noexcept = 0;
  virtual void GetAllEntitiesImpl(EntityBuffer& buffer) const = 0;
  virtual bool HasSinglenentsImpl(
      const internal::DynamicXnentMask& mask) const noexcept = 0;
  virtual void AddSinglenentImpl(internal::XnentTypeID idx,
                                 Xnent& singlenent) = 0;
  virtual Xnent& RemoveSinglenentImpl(internal::XnentTypeID idx) noexcept = 0;
  virtual const Xnent& GetSinglenentImpl(
      internal::XnentTypeID idx) const noexcept = 0;
  virtual Xnent& GetSinglenentImpl(internal::XnentTypeID idx) noexcept = 0;
};

class IWorldFactory {
 public:
  std::unique_ptr<IWorld> CreateWorld() const { return CreateWorldImpl(); }

 private:
  virtual std::unique_ptr<IWorld> CreateWorldImpl() const = 0;
};

namespace internal {

void SnapshotImpl(const DynamicXnentMask& comp_mask,
                  const DynamicXnentMask& single_mask, const IWorld& src,
                  IWorld& dest);
void MergeImpl(const DynamicXnentMask& comp_mask,
               const DynamicXnentMask& single_mask, const IWorld& src,
               IWorld& dest);

}  // namespace internal

template <typename NeedList>
void Snapshot(NeedList need_list, const IWorld& src, IWorld& dest) {
  using ComponentList = typename NeedList::ComponentList;
  using SinglenentList = typename NeedList::SinglenentList;
  internal::SnapshotImpl(internal::GetXnentMask(ComponentList{}),
                         internal::GetXnentMask(SinglenentList{}), src, dest);
}

template <typename ComponentList>
void Merge(ComponentList comp_list, const IWorld& src, IWorld& dest) {
  internal::MergeImpl(internal::GetXnentMask(ComponentList{}),
                      internal::GetXnentMask(SinglenentList{}), src, dest);
}

}  // namespace einu