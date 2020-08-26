#pragma once

#include <vector>

namespace ecs {
template <typename T, typename Allocator = std::allocator<T>>
class AutoGrowVector : public std::vector<T, Allocator> {
 public:
  using vector = std::vector<T, Allocator>;
  using vector::vector;

  vector::reference operator[](vector::size_type pos) {
    if (pos >= vector::size()) {
      vector::resize(pos + 1);
    }
    return vector::operator[](pos);
  }

  vector::reference at(vector::size_type pos) = delete;
};
}