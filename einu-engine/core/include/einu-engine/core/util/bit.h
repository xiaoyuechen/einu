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
