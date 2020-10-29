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

#include "src/sys_starchaser.h"

#include <glm/glm.hpp>

#include "src/sys_find_path.h"

namespace astar {
namespace sys {

void MoveAlongPath(const sgl::WorldState& world_state,
                   const einu::cmp::Transform& transform,
                   einu::cmp::Movement& movement,
                   cmp::PathFinding& path_finding) {
  static constexpr float kArriveRadius = 1.0f;

  // TODO(Xiaoyue Chen): HACK. Need to properly offset
  glm::vec2 offset = sgl::GetCellSize(world_state) / 2.f;
  auto next_way_point = glm::vec3(
      glm::vec2(path_finding.path.back()) * sgl::GetCellSize(world_state) +
          offset,
      0);
  if (glm::distance(next_way_point, transform.GetPosition()) < kArriveRadius) {
    path_finding.path.pop_back();
  } else {
    auto dp = next_way_point - transform.GetPosition();
    movement.direction = glm::normalize(dp);
    movement.speed = movement.max_speed;
  }
}

void RunStarChaserFSM(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);
  if (starchaser.state == cmp::Starchaser::State::Collecting) {
    FindPath(world_state, path_finding, transform.GetPosition(),
             world_state.star_pos);
    starchaser.state = cmp::Starchaser::State::Enroute;
  } else if (starchaser.state == cmp::Starchaser::State::Enroute) {
    if (path_finding.path.size() == 0) {
      return;
    }
    MoveAlongPath(world_state, transform, movement, path_finding);
  }
}

}  // namespace sys
}  // namespace astar
