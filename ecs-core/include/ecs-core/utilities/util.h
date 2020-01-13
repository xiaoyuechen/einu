#pragma once
#include <typeindex>

namespace ecs {
namespace util {
template<typename T>
std::type_index get_type_index();




template <typename T>
std::type_index get_type_index() {
  return std::type_index(typeid(T));
}
}  // namespace util
}