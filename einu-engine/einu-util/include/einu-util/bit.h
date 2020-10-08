#pragma once

#include <algorithm>
#include <vector>

namespace einu {
namespace util {

// TODO(Xiaoyue Chen): use architecture specific ffs instruction instead
std::size_t FindFirstSet(std::vector<bool>::const_iterator begin,
                         std::vector<bool>::const_iterator end) noexcept {
  auto it = std::find(begin, end, true);
  return std::distance(begin, it);
}

}  // namespace util
}  // namespace einu