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

template <std::size_t begin, typename Fn, std::size_t... Is>
constexpr void static_for_impl(Fn&& fn, std::index_sequence<Is...>) {
  (fn(std::integral_constant<std::size_t, begin + Is>{}), ...);
}

}  // namespace internal

template <std::size_t begin, std::size_t end, typename Fn>
constexpr void static_for(Fn&& fn) {
  internal::static_for_impl<begin>(std::forward<Fn>(fn),
                                   std::make_index_sequence<end - begin>{});
}

}  // namespace tmp
}  // namespace einu
