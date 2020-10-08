#pragma once

#include <memory>

#include "einu-core/entity_buffer.h"
#include "einu-core/i_entity.h"
#include "einu-core/internal/component_mask.h"
#include "einu-core/internal/singlenent_index.h"
#include "einu-core/need_list.h"

namespace einu {

class IWorld {
 public:
  virtual void AddEntity(IEntity& ett) = 0;
  virtual void RemoveEntity(const IEntity& ett) noexcept = 0;
  virtual IEntity& GetEntity(EID eid) noexcept = 0;
  virtual const IEntity& GetEntity(EID eid) const noexcept = 0;
  virtual std::size_t GetEntityCount() const noexcept = 0;
  virtual void GetEntities(EntityBuffer& buffer) const = 0;
  template <typename Singlenent>
  const Singlenent& GetSinglenent() const noexcept {
    return GetSinglenent(internal::GetSinglenentIndex<Singlenent>());
  }

 protected:
  virtual const ISinglenent& GetSinglenent(
      internal::SinglenentIndex idx) const noexcept = 0;
};

class IWorldFactory {
 public:
  virtual std::unique_ptr<IWorld> CreateWorld() = 0;
};

namespace internal {

void Snapshot(const ComponentMask& list, const IWorld& src, IWorld& dest);
void Merge(const ComponentMask& list, const IWorld& src, IWorld& dest);

}  // namespace internal

template <typename ComponentList>
void Snapshot(ComponentList comp_list, const IWorld& src, IWorld& dest) {
  internal::Snapshot(internal::GetComponentIndexList(comp_list), src, dest);
}

template <typename ComponentList>
void Merge(ComponentList comp_list, const IWorld& src, IWorld& dest) {
  internal::Merge(internal::GetComponentIndexList(comp_list), src, dest);
}

}  // namespace einu