#pragma once

#include <cassert>

#include "einu-rtti/class_index.h"

namespace einu {
namespace rtti {

namespace internal {
template <typename T>
struct ClassIndexStorage {
  inline static ClassIndex value = ClassIndex();
};
}  // namespace internal

template <typename T>
void SetClassIndex(ClassIndex idx) noexcept {
  auto& v = internal::ClassIndexStorage<std::decay<T>::type>::value;
  assert(!IsAssigned(v) && "class index of <T> is already set");
  v = idx;
}

template <typename T>
ClassIndex GetClassIndex() noexcept {
  return internal::ClassIndexStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace einu
