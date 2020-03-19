#pragma once

#include <cstddef>

namespace ecs {
template <typename T>
constexpr std::size_t GetEnumCount() {
  return static_cast<std::size_t>(T::COUNT);
}

}  // namespace ecs

