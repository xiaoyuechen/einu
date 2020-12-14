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

#include "einu-engine/ai/bt_move_to.h"

#include "einu-engine/ai/cmp_destination.h"
#include "einu-engine/common/cmp_movement.h"
#include "einu-engine/common/cmp_transform.h"

namespace einu {
namespace ai {
namespace bt {

Result MoveTo::Run(const ArgPack& args) {
  const auto& transform = args.GetComponent<const einu::cmp::Transform>();
  const auto& destination = args.GetComponent<const ai::cmp::Destination>();
  auto& movement = args.GetComponent<einu::cmp::Movement>();

  auto delta = destination.destination - transform.GetPosition();
  if (glm::length2(delta) < glm::pow(destination.tolerance_radius, 2)) {
    movement.direction = glm::vec3();
    return Result::Success;
  }

  movement.direction = glm::normalize(delta);
  movement.speed = movement.max_speed;
  return Result::Running;
}

}  // namespace bt
}  // namespace ai
}  // namespace einu
