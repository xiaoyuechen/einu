#pragma once

#include <cassert>

#include "einu-rtti/class_index.h"

namespace einu {
namespace rtti {

namespace detail {
template <typename T>
struct ClassIndexStorage {
  inline static ClassIndex value = ClassIndex();
};
}  // namespace detail

template <typename T>
void SetClassIndex(ClassIndex idx) noexcept {
  auto& v = detail::ClassIndexStorage<std::decay<T>::type>::value;
  assert(v == ClassIndex() && "class index of <T> is already set");
  v = idx;
}

template <typename T>
ClassIndex GetClassIndex() noexcept {
  return detail::ClassIndexStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace einu
