// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
