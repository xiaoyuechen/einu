#pragma once

#include "ecs-rtti/class_index.h"

namespace ecs {
namespace rtti {

namespace detail {
template <typename T>
struct ClassIndexStorage {
  inline static ClassIndex value = ClassIndex();
};
}  // namespace detail

template <typename T>
ClassIndex GetClassIndex() noexcept {
  return detail::ClassIndexStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace ecs
