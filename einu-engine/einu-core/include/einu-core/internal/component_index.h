#pragma once

#include <einu-rtti/class_index_storage.h>

#include <type_traits>

#include "einu-core/i_component.h"

namespace einu {
namespace internal {

class ComponentIndex : public rtti::ClassIndex {
 public:
  using rtti::ClassIndex::ClassIndex;
};

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
  return ComponentIndex(rtti::GetClassIndex<T>());
}

}  // namespace internal
}  // namespace einu