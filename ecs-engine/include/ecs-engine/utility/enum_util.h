#ifndef ENUM_UTIL_H_
#define ENUM_UTIL_H_

#include <cstddef>

namespace ecs {
template <typename T>
constexpr std::size_t GetEnumCount() {
  return static_cast<std::size_t>(T::COUNT);
}

}  // namespace ecs

#endif  // ENUM_UTIL_H_
