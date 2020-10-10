#pragma once

#include "einu-engine/core/component_mask.h"
#include "einu-engine/utility/algorithm.h"
#include "einu-engine/utility/tmp/type_list.h"

namespace einu {
namespace detail {

template <typename T>
void SetBit(DynamicXnentMask& mask) noexcept {
  auto idx = rtti::GetTypeID<T>();
  assert(idx != rtti::TypeID() && "<T> is not registered");
  mask.set(idx);
}

template <typename... Ts>
DynamicXnentMask& GetComponentMask() {
  static DynamicXnentMask value = [] {
    DynamicXnentMask mask;
    (SetBit<Ts>(mask), ...);
    return mask;
  }();
  return value;
}

}  // namespace detail
}  // namespace einu