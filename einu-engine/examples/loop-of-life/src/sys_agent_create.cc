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

#include "src/sys_agent_create.h"

#include <einu-engine/ai/cmp_destination.h>
#include <einu-engine/common/cmp_movement.h>
#include <einu-engine/common/cmp_transform.h>
#include <einu-engine/graphics/cmp_sprite.h>

#include "src/cmp_agent.h"

namespace lol {
namespace sys {

einu::EID CreateSheep(einu::IEntityManager& ett_mgr,
                      const einu::common::Transform& transform, float max_speed,
                      const glm::vec4& color, const char* sprite_name) {
  auto ett = ett_mgr.CreateEntity();
  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = color;
  sprite.sprite_name = sprite_name;
  ett_mgr.AddComponent<einu::common::cmp::Transform>(ett) =
      einu::common::cmp::Transform{transform};
  auto& movement = ett_mgr.AddComponent<einu::common::cmp::Movement>(ett);
  movement.max_speed = max_speed;
  auto& dest = ett_mgr.AddComponent<einu::ai::cmp::Destination>(ett);
  dest.destination = glm::vec3(100, 100, 0);
  ett_mgr.AddComponent<cmp::Agent>(ett).type = AgentType::Sheep;
  return ett;
}

}  // namespace sys
}  // namespace lol
