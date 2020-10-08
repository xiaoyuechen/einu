#pragma once

#include <array>
#include <cassert>
#include <cstddef>

#include "einu-core/i_entity.h"

namespace einu {
namespace internal {

template <int max_comp>
using StaticComponentTable = std::array<Xnent*, max_comp>;

template <int max_comp>
class Entity : public IEntity {
 public:
  using StaticXnentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;

  Entity(EID eid, StaticXnentMask& mask, ComponentTable& table) noexcept
      : eid_{eid}
      , mask_{mask}
      , table_{table} {}

  EID GetID() const noexcept override final { return eid_; }

 private:
  bool HasComponentsImpl(const XnentMask& mask) const noexcept override final {
    return (mask & mask_) == mask;
  }

  const Xnent& GetComponentImpl(XnentIndex idx) const noexcept override final {
    return *table_[idx];
  }

  Xnent& GetComponentImpl(XnentIndex idx) noexcept override final {
    return *table_[idx];
  }

  void AddComponentImpl(XnentIndex idx, Xnent& comp) override final {
    assert(!mask_[idx] && "already have component");
    table_[idx] = &comp;
    mask_[idx] = true;
  }

  Xnent& RemoveComponentImpl(XnentIndex idx) noexcept override final {
    assert(mask_[idx] && "do not have component");
    mask_[idx] = false;
    auto& tmp = *table_[idx];
    table_[idx] = nullptr;
    return tmp;
  }

  EID eid_ = ~EID{0};
  StaticXnentMask& mask_;
  ComponentTable& table_;
};

}  // namespace internal
}  // namespace einu