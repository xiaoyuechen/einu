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

#include "einu-engine/core/xnent.h"

namespace einu {
namespace sgl {

struct Time : public Xnent {
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  TimePoint pre;
  TimePoint now;
};

constexpr float DeltaSeconds(const Time& time) noexcept {
  std::chrono::duration<float> dt = time.now - time.pre;
  return dt.count();
}

}  // namespace sgl
}  // namespace einu
