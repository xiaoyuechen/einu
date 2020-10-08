#pragma once

#include "einu-engine/core/component_mask.h"
#include "einu-engine/utility/algorithm.h"
#include "einu-engine/utility/tmp/type_list.h"

namespace einu {
namespace detail {

template <typename T>
void SetBit(XnentMask& mask) noexcept {
  auto idx = rtti::GetClassIndex<T>();
  assert(idx != rtti::ClassIndex() && "<T> is not registered");
  mask.set(idx);
}

template <typename... Ts>
XnentMask& GetComponentMask() {
  static XnentMask value = [] {
    XnentMask mask;
    (SetBit<Ts>(mask), ...);
    return mask;
  }();
  return value;
}

}  // namespace detail
}  // namespace einu