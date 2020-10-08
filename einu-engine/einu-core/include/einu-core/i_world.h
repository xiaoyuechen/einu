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
  bool HasSinglenents(SinglenentList l) const noexcept {
    return HasSinglenents(internal::GetXnentMask(l));
  }

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
    return GetSinglenent(internal::GetXnentIndex<Singlenent>());
  }

 protected:
  virtual bool HasSinglenents(
      const internal::XnentMask& mask) const noexcept = 0;
  virtual void AddSinglenent(internal::XnentIndex idx, Xnent& singlenent) = 0;
  virtual Xnent& RemoveSinglenent(internal::XnentIndex idx) noexcept = 0;
  virtual const Xnent& GetSinglenent(
      internal::XnentIndex idx) const noexcept = 0;
  virtual Xnent& GetSinglenent(internal::XnentIndex idx) noexcept = 0;
};

class IWorldFactory {
 public:
  virtual std::unique_ptr<IWorld> CreateWorld() = 0;
};

namespace internal {

void Snapshot(const XnentMask& comp_mask, const XnentMask& single_mask,
              const IWorld& src, IWorld& dest);
void Merge(const XnentMask& comp_mask, const XnentMask& single_mask,
           const IWorld& src, IWorld& dest);

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