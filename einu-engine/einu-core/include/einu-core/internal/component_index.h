#pragma once

#include <einu-rtti/class_index_storage.h>

#include <type_traits>

namespace einu {
namespace internal {

using ComponentIndex = rtti::ClassIndex;

template <typename T>
void SetComponentIndex(ComponentIndex idx) {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "<IComponent> must be base of <T>");
  rtti::SetClassIndex<T>(idx);
}

template <typename T>
ComponentIndex GetComponentIndex() {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "<IComponent> must be base of <T>");
  return rtti::GetClassIndex<T>();
}

}  // namespace internal
}  // namespace einu