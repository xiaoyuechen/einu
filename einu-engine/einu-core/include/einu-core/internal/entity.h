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
class Entity final : public IEntity {
 public:
  using StaticXnentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;

  Entity(EID eid, StaticXnentMask& mask, ComponentTable& table) noexcept
      : eid_{eid}
      , mask_{mask}
      , table_{table} {}

 private:
  EID GetIDImpl() const noexcept override { return eid_; }

  bool HasComponentsImpl(const DynamicXnentMask& mask) const noexcept override {
    return (mask & mask_) == mask;
  }

  const Xnent& GetComponentImpl(XnentTypeID idx) const noexcept override {
    return *table_[idx];
  }

  Xnent& GetComponentImpl(XnentTypeID idx) noexcept override {
    return *table_[idx];
  }

  void AddComponentImpl(XnentTypeID idx, Xnent& comp) override {
    assert(!mask_[idx] && "already have component");
    table_[idx] = &comp;
    mask_[idx] = true;
  }

  Xnent& RemoveComponentImpl(XnentTypeID idx) noexcept override {
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