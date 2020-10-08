#pragma once

#include <memory>

#include "einu-core/entity_buffer.h"
#include "einu-core/i_entity.h"
#include "einu-core/internal/xnent_mask.h"
#include "einu-core/need_list.h"

namespace einu {

class IWorld {
 public:
  virtual void AddEntity(IEntity& ett) = 0;
  virtual void RemoveEntity(EID eid) noexcept = 0;
  virtual IEntity& GetEntity(EID eid) noexcept = 0;
  virtual const IEntity& GetEntity(EID eid) const noexcept = 0;
  virtual std::size_t GetEntityCount() const noexcept = 0;
  virtual void GetEntities(EntityBuffer& buffer) const = 0;

  template <typename Singlenent>
  void AddSinglenent(Singlenent& singlenent) {
    AddSinglenent(internal::GetXnentIndex<Singlenent>(), singlenent);
  }

  template <typename Singlenent>
  Singlenent& RemoveSinglenent() noexcept {
    return RemoveSinglenent(internal::GetXnentIndex<Singlenent>());
  }

  template <typename Singlenent>
  const Singlenent& GetSinglenent() const noexcept {
    return GetSinglenent(internal::GetXnentIndex<Singlenent>());
  }

  template <typename Singlenent>
  Singlenent& GetSinglenent() noexcept {
    return const_cast<Singlenent&>(
        static_cast<const IWorld&>(*this).GetSinglenent<Singlenent>());
  }

 protected:
  virtual void AddSinglenent(internal::XnentIndex idx,
                             Xnent& singlenent) = 0;
  virtual Xnent& RemoveSinglenent(
      internal::XnentIndex idx) noexcept = 0;
  virtual const Xnent& GetSinglenent(
      internal::XnentIndex idx) const noexcept = 0;
};

class IWorldFactory {
 public:
  virtual std::unique_ptr<IWorld> CreateWorld() = 0;
};

namespace internal {

void Snapshot(const XnentMask& list, const IWorld& src, IWorld& dest);
void Merge(const XnentMask& list, const IWorld& src, IWorld& dest);

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