#pragma once

#include <cstddef>
#include <functional>

namespace einu {
namespace internal {

using GrowthFunc = std::function<std::size_t(std::size_t)>;

constexpr std::size_t DefaultGrowFunc(std::size_t pool_size) noexcept {
  return pool_size == 0 ? 1 : 2 * pool_size;
}

template <typename... T>
struct PoolPolicy;

template <typename T>
struct PoolPolicy<T> {
  using size_type = std::size_t;
  using value_type = T;

  PoolPolicy(size_type init_size, std::unique_ptr<value_type> value = nullptr,
             GrowthFunc growth_func = DefaultGrowFunc) noexcept
      : init_size(init_size),
        value(std::move(value)),
        growth_func(growth_func) {}

  size_type init_size;
  std::unique_ptr<value_type> value;
  GrowthFunc growth_func;
};

template <>
struct PoolPolicy<> {
  using size_type = std::size_t;

  PoolPolicy(size_type init_size,
             GrowthFunc growth_func = DefaultGrowFunc) noexcept
      : init_size(init_size), growth_func(growth_func) {}

  size_type init_size;
  GrowthFunc growth_func;
};

}  // namespace internal
}  // namespace einu
