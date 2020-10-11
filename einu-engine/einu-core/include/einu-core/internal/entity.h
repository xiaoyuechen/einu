#pragma once

#include <array>
#include <cassert>
#include <cstddef>

#include "einu-core/i_entity.h"

namespace einu {
namespace internal {

template <std::size_t max_comp>
using StaticComponentTable = std::array<Xnent*, max_comp>;

template <std::size_t max_comp>
class Entity final : public IEntity {
 public:
  using StaticXnentMask = StaticXnentMask<max_comp>;
  using ComponentTable = StaticComponentTable<max_comp>;

  Entity() noexcept = default;
  Entity(EID id, StaticXnentMask& mask, ComponentTable& table) noexcept
      : id(id)
      , mask(&mask)
      , table(&table) {}

  EID id = ~EID{0};
  StaticXnentMask* mask = nullptr;
  ComponentTable* table = nullptr;

 private:
  EID GetIDImpl() const noexcept override { return id; }

  bool HasComponentsImpl(const DynamicXnentMask& mask) const noexcept override {
    return (mask & Mask()) == mask;
  }

  const Xnent& GetComponentImpl(XnentTypeID idx) const noexcept override {
    return *Table()[idx];
  }

  Xnent& GetComponentImpl(XnentTypeID idx) noexcept override {
    return *Table()[idx];
  }

  void AddComponentImpl(XnentTypeID idx, Xnent& comp) override {
    assert(!Mask()[idx] && "already have component");
    Table()[idx] = &comp;
    Mask()[idx] = true;
  }

  Xnent& RemoveComponentImpl(XnentTypeID idx) noexcept override {
    assert(Mask()[idx] && "do not have component");
    Mask()[idx] = false;
    auto& tmp = *Table()[idx];
    Table()[idx] = nullptr;
    return tmp;
  }

  const StaticXnentMask& Mask() const noexcept { return *mask; }
  StaticXnentMask& Mask() noexcept { return *mask; }
  const ComponentTable& Table() const noexcept { return *table; }
  ComponentTable& Table() noexcept { return *table; }
};

}  // namespace internal
}  // namespace einu