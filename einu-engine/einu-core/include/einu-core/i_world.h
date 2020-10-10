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

  template <typename SinglenentList>
  bool HasSinglenents(
      SinglenentList l,
      const internal::DynamicXnentMask& mask =
          internal::GetXnentMask(SinglenentList{})) const noexcept {
    return HasSinglenents(mask);
  }

  template <typename Singlenent>
  void AddSinglenent(Singlenent& singlenent,
                     internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) {
    AddSinglenent(id, singlenent);
  }

  template <typename Singlenent>
  Singlenent& RemoveSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) noexcept {
    return RemoveSinglenent(id);
  }

  template <typename Singlenent>
  const Singlenent& GetSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) const noexcept {
    return GetSinglenent(id);
  }

  template <typename Singlenent>
  Singlenent& GetSinglenent(
      internal::XnentTypeID id = GetXnentTypeID<Singlenent>()) noexcept {
    return GetSinglenent(id);
  }

 protected:
  virtual bool HasSinglenents(
      const internal::DynamicXnentMask& mask) const noexcept = 0;
  virtual void AddSinglenent(internal::XnentTypeID idx, Xnent& singlenent) = 0;
  virtual Xnent& RemoveSinglenent(internal::XnentTypeID idx) noexcept = 0;
  virtual const Xnent& GetSinglenent(
      internal::XnentTypeID idx) const noexcept = 0;
  virtual Xnent& GetSinglenent(internal::XnentTypeID idx) noexcept = 0;
};

class IWorldFactory {
 public:
  virtual std::unique_ptr<IWorld> CreateWorld() = 0;
};

namespace internal {

void Snapshot(const DynamicXnentMask& comp_mask,
              const DynamicXnentMask& single_mask, const IWorld& src,
              IWorld& dest);
void Merge(const DynamicXnentMask& comp_mask,
           const DynamicXnentMask& single_mask, const IWorld& src,
           IWorld& dest);

}  // namespace internal

template <typename NeedList>
void Snapshot(NeedList need_list, const IWorld& src, IWorld& dest) {
  using ComponentList = typename NeedList::ComponentList;
  using SinglenentList = typename NeedList::SinglenentList;
  internal::Snapshot(internal::GetXnentMask(ComponentList{}),
                     internal::GetXnentMask(SinglenentList{}), src, dest);
}

template <typename ComponentList>
void Merge(ComponentList comp_list, const IWorld& src, IWorld& dest) {
  internal::Merge(internal::GetXnentMask(ComponentList{}),
                  internal::GetXnentMask(SinglenentList{}), src, dest);
}

}  // namespace einu