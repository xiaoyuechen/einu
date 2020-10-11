#pragma once

#include <memory>

#include "einu-core/entity_buffer.h"
#include "einu-core/i_entity.h"
#include "einu-core/internal/xnent_mask.h"
#include "einu-core/need_list.h"

namespace einu {

class IWorld {
 public:
  virtual ~IWorld() = default;

  void AddEntity(IEntity& ett) { AddEntityImpl(ett); }
  void RemoveEntity(EID eid) { RemoveEntityImpl(eid); }
  IEntity& GetEntity(EID eid) noexcept { return GetEntityImpl(eid); }
  const IEntity& GetEntity(EID eid) const noexcept {
    return GetEntityImpl(eid);
  }
  std::size_t GetEntityCount() const noexcept { return GetEntityCountImpl(); }
  void GetAllEntities(EntityBuffer& buffer) const {
    return GetAllEntitiesImpl(buffer);
  }

  IEntity& GetSinglenity() noexcept { return GetSinglenityImpl(); }
  const IEntity& GetSinglenity() const noexcept { return GetSinglenityImpl(); }

 private:
  virtual void AddEntityImpl(IEntity& ett) = 0;
  virtual void RemoveEntityImpl(EID eid) = 0;
  virtual IEntity& GetEntityImpl(EID eid) noexcept = 0;
  virtual const IEntity& GetEntityImpl(EID eid) const noexcept = 0;
  virtual std::size_t GetEntityCountImpl() const noexcept = 0;
  virtual void GetAllEntitiesImpl(EntityBuffer& buffer) const = 0;
  virtual IEntity& GetSinglenityImpl() noexcept = 0;
  virtual const IEntity& GetSinglenityImpl() const noexcept = 0;
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