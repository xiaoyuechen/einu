#pragma once

namespace einu {

using GrowthFunc = std::function<std::size_t(std::size_t)>;

constexpr std::size_t DefaultComponentPoolGrowFunc(
    std::size_t pool_size) noexcept {
  return pool_size == 0 ? 1 : 2 * pool_size;
}

template <typename T>
struct PoolPolicy {
  using size_type = std::size_t;
  using value_type = T;

  constexpr PoolPolicy(
      size_type init_size, const value_type& value = value_type{},
      GrowthFunc growth_func = DefaultComponentPoolGrowFunc) noexcept
      : init_size(init_size)
      , value(value)
      , growth_func(growth_func) {}

  size_type init_size;
  value_type value;
  GrowthFunc growth_func;
};

}  // namespace einu