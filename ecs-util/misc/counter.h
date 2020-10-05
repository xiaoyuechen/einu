#pragma once

namespace einu {
namespace misc {

template <typename size_type>
class Counter {
 public:
  explicit constexpr Counter(size_type start = 0) noexcept { count_ = start; }

  constexpr void CountUp(size_type step = 1) noexcept { count_ += step; }
  constexpr void CountDown(size_type step = 1) noexcept { count_ -= step; }
  size_type GetCount() const noexcept { return count_; }

 private:
  size_type count_ = 0;
};

}  // namespace misc
}  // namespace einu