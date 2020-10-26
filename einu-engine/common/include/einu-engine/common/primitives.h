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

#include <array>

namespace einu {
namespace common {

template <typename T>
struct Rect : public std::array<T, 4> {
  T Left() const noexcept { return (*this)[0]; }
  T& Left() noexcept { return (*this)[0]; }
  T Buttom() const noexcept { return (*this)[1]; }
  T& Buttom() noexcept { return (*this)[1]; }
  T Width() const noexcept { return (*this)[2]; }
  T& Width() noexcept { return (*this)[2]; }
  T Height() const noexcept { return (*this)[3]; }
  T& Height() noexcept { return (*this)[3]; }
};

using FloatRect = Rect<float>;
using IntRect = Rect<int>;

}  // namespace common
}  // namespace einu
