#pragma once

#include <algorithm>
#include <vector>

namespace einu {
namespace util {

// TODO(Xiaoyue Chen): This is extremely slow. Use architecture specific ffs
// instruction instead.
// std::size_t FindFirstSet(std::vector<bool>::const_iterator begin,
//                         std::vector<bool>::const_iterator end) noexcept {
//  auto it = std::find(begin, end, true);
//  return std::distance(begin, it);
//}

// TODO(Xiaoyue Chen): This is a temporary solution. It uses more memory. We
// need to support an actual bit array.
inline std::size_t FindFirstSet(
    std::vector<std::uint8_t>::const_iterator begin,
    std::vector<std::uint8_t>::const_iterator end) noexcept {
  auto it = std::find(begin, end, true);
  return std::distance(begin, it);
}

}  // namespace util
}  // namespace einu
