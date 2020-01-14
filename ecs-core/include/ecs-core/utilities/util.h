#pragma once
#include <typeindex>

namespace ecs {
namespace util {
template <typename T>
std::type_index get_type_index();
}
}  // namespace ecs

namespace ecs {
namespace util {
template <typename T>
std::type_index get_type_index() {
  return std::type_index(typeid(T));
}
}  // namespace util
}  // namespace ecs