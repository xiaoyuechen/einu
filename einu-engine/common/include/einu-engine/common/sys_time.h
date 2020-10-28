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

#include <chrono>
#include <utility>

#include "einu-engine/common/sgl_time.h"

namespace einu {
namespace sys {

inline void InitTime(sgl::Time& time) noexcept {
  time.now = std::chrono::system_clock::now();
}

inline void UpdateTime(sgl::Time& time) noexcept {
  std::swap(time.now, time.pre);
  time.now = std::chrono::system_clock::now();
}

}  // namespace sys
}  // namespace einu
