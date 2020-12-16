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

#include "src/sys_create_entity.h"

#include "bitplusplus/enum.h"
#include "einu-engine/ai/cmp_destination.h"
#include "einu-engine/common/cmp_movement.h"
#include "einu-engine/common/cmp_transform.h"
#include "einu-engine/common/random.h"
#include "einu-engine/graphics/cmp_sprite.h"
#include "src/cmp.h"
#include "src/sgl_world_state.h"

namespace astar {
namespace sys {

einu::EID CreateCellFrame(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 255, 255};
  sprite.sprite_name = kCellFrameSprite;

  ett_mgr.AddComponent<cmp::CellFrameTag>(ett);

  return ett;
}

einu::EID CreateCellBlock(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& cell = ett_mgr.AddComponent<cmp::Cell>(ett);
  cell.pos =
      sgl::GetCoordsInGrid(world_state, glm::vec2(transform.GetPosition()));

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 255, 255};
  sprite.sprite_name = kCellBlockSprite;

  return ett;
}

einu::EID CreateSpaceship(einu::IEntityManager& ett_mgr,
                          const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  world_state.spaceship_eid = ett;

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{50, 255, 255, 255};
  sprite.sprite_name = kSpaceshipSprite;

  return ett;
}

einu::EID CreateTradingPost(einu::IEntityManager& ett_mgr,
                            const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  world_state.traiding_post_eid = ett;

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 0, 0, 255};
  sprite.sprite_name = kTradingPostSprite;

  return ett;
}

einu::EID CreateStar(einu::IEntityManager& ett_mgr,
                     const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};

  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  world_state.star_eid = ett;

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 0, 255};
  sprite.sprite_name = kStarSprite;

  return ett;
}

einu::EID CreateStarchaser(einu::IEntityManager& ett_mgr,
                           const einu::Transform& transform) {
  auto ett = ett_mgr.CreateEntity();

  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  glm::vec2 offset = sgl::GetCellSize(world_state) / 2.f;

  auto& transform_cmp = ett_mgr.AddComponent<einu::cmp::Transform>(ett) =
      einu::cmp::Transform{transform};
  transform_cmp.SetPosition(transform_cmp.GetPosition() + glm::vec3(offset, 0));

  auto& movement = ett_mgr.AddComponent<einu::cmp::Movement>(ett);
  movement.max_speed = 60.f;

  auto& sprite = ett_mgr.AddComponent<einu::graphics::cmp::Sprite>(ett);
  sprite.color = glm::vec4{255, 255, 0, 255};
  sprite.sprite_name = kStarchaserSprite;

  ett_mgr.AddComponent<cmp::Starchaser>(ett);

  ett_mgr.AddComponent<cmp::PathFinding>(ett);

  ett_mgr.AddComponent<cmp::StarPocket>(ett);

  ett_mgr.AddComponent<cmp::Energy>(ett);

  return ett;
}

}  // namespace sys
}  // namespace astar
