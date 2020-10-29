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

#include <einu-engine/common/cmp_movement.h>
#include <einu-engine/common/cmp_transform.h>
#include <einu-engine/common/sgl_time.h>

#include <algorithm>

#include "src/sgl_world_state.h"

namespace astar {
namespace sys {

inline void Move(const einu::sgl::Time& time,
                 const sgl::WorldState& world_state,
                 einu::cmp::Transform& transform,
                 einu::cmp::Movement& movement) {
  auto dp = movement.direction * movement.speed * einu::sgl::DeltaSeconds(time);
  auto np = transform.GetPosition() + dp;
  auto world_size = world_state.world_size;
  np.x = std::clamp(np.x, 0.f, world_size.x);
  np.y = std::clamp(np.y, 0.f, world_size.y);
  transform.SetPosition(np);
  movement.speed = 0.f;
}

}  // namespace sys
}  // namespace astar
