#pragma once

#include <cassert>
#include <functional>
#include <vector>

#include "einu-util/bit.h"

namespace einu {
namespace util {

template <typename T>
class FixedPool {
 public:
  using size_type = std::size_t;
  using value_type = T;

  explicit FixedPool(size_type count)
      : object_arr_(count)
      , bit_arr_(count, true) {}

  FixedPool(size_type count, const T& value)
      : object_arr_(count, value)
      , bit_arr_(count, true) {}

  FixedPool(const FixedPool&) = delete;
  FixedPool& operator=(const FixedPool&) = delete;

  size_type Size() const noexcept { return object_arr_.size(); }
  size_type FreePos() const noexcept {
    return FindFirstSet(bit_arr_.begin(), bit_arr_.end());
  }

  [[nodiscard]] T& Acquire() noexcept {
    auto free_pos = FreePos();
    assert(free_pos != bit_arr_.size() && "no object available");
    bit_arr_[free_pos] = false;
    return object_arr_[free_pos];
  }

  void Release(const T& obj) noexcept {
    auto idx = &obj - object_arr_.data();
    assert(!bit_arr_[idx] && "object is already released");
    bit_arr_[idx] = true;
  }

 private:
  std::vector<T> object_arr_;
  std::vector<bool> bit_arr_;
};

template <typename T>
bool AllAcquired(const FixedPool<T>& pool) noexcept {
  return pool.FreePos() == pool.Size();
}

}  // namespace util
}  // namespace einu