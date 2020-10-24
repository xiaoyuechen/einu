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

#include <cstdint>
#include <utility>

namespace einu {
namespace tmp {

namespace internal {
template <typename Predicate, std::size_t... Is>
constexpr void StaticForImpl(Predicate&& pred, std::index_sequence<Is...>) {
  (pred(std::integral_constant<std::size_t, Is>{}), ...);
}
}  // namespace internal

template <std::size_t count, typename Predicate>
constexpr void StaticFor(Predicate&& pred) {
  internal::StaticForImpl(std::forward<Predicate>(pred),
                          std::make_index_sequence<count>{});
}

}  // namespace tmp
}  // namespace einu
