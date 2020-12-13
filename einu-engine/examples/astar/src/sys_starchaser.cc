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

#include <einu-engine/common/sgl_time.h>

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

bool HasReached(const sgl::WorldState& world_state, glm::vec2 pos,
                glm::vec2 target) noexcept {
  static constexpr float kReachRange = 50.0f;
  // glm::vec2 offset = sgl::GetCellSize(world_state) / 2.f;
  return glm::distance(pos, target) < kReachRange;
}

void CollectStar(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);
  auto star_pos =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.star_eid)
          .GetPosition();

  using State = cmp::Starchaser::State;

  if (path_finding.path.size() == 0) {
    if (HasReached(world_state, transform.GetPosition(), star_pos)) {
      starchaser.state = State::Selling;
    } else {
      FindPath(world_state, path_finding, transform.GetPosition(), star_pos);
    }
  } else {
    MoveAlongPath(world_state, transform, movement, path_finding);
  }
}

void SellStar(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);
  auto& energy = ett_mgr.GetComponent<cmp::Energy>(eid);
  auto& time = ett_mgr.GetSinglenent<einu::sgl::Time>();
  auto& star_transform =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.star_eid);
  auto& trading_post_transform =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.traiding_post_eid);

  energy.energy -= energy.energy_lost_rate * einu::sgl::DeltaSeconds(time);

  using State = cmp::Starchaser::State;

  if (energy.energy < energy.fatigue_threshold) {
    path_finding.path.clear();
    starchaser.state = State::GoingHome;
  } else {
    if (path_finding.path.size() == 0) {
      if (HasReached(world_state, trading_post_transform.GetPosition(),
                     transform.GetPosition())) {
        starchaser.state = State::Done;
      } else {
        FindPath(world_state, path_finding, transform.GetPosition(),
                 trading_post_transform.GetPosition());
      }
    } else {
      MoveAlongPath(world_state, transform, movement, path_finding);
      star_transform.SetPosition(transform.GetPosition());
    }
  }
}

void GoHome(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);
  auto& energy = ett_mgr.GetComponent<cmp::Energy>(eid);
  auto& time = ett_mgr.GetSinglenent<einu::sgl::Time>();
  auto& star_transform =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.star_eid);
  auto home_pos =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.spaceship_eid)
          .GetPosition();

  using State = cmp::Starchaser::State;

  if (path_finding.path.size() == 0) {
    if (HasReached(world_state, home_pos, transform.GetPosition())) {
      starchaser.state = State::Resting;
    } else {
      FindPath(world_state, path_finding, transform.GetPosition(), home_pos);
    }
  } else {
    MoveAlongPath(world_state, transform, movement, path_finding);
  }
}

void Rest(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);
  auto& energy = ett_mgr.GetComponent<cmp::Energy>(eid);
  auto& time = ett_mgr.GetSinglenent<einu::sgl::Time>();
  auto& star_transform =
      ett_mgr.GetComponent<einu::cmp::Transform>(world_state.star_eid);

  using State = cmp::Starchaser::State;

  energy.energy += energy.energy_gain_rate * einu::sgl::DeltaSeconds(time);

  if (energy.energy >= energy.max_energy) {
    starchaser.state = State::Collecting;
  }
}

void RunStarChaserFSM(einu::IEntityManager& ett_mgr, einu::EID eid) {
  auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  auto& transform = ett_mgr.GetComponent<einu::cmp::Transform>(eid);
  auto& movement = ett_mgr.GetComponent<einu::cmp::Movement>(eid);
  auto& path_finding = ett_mgr.GetComponent<cmp::PathFinding>(eid);
  auto& starchaser = ett_mgr.GetComponent<cmp::Starchaser>(eid);

  using State = cmp::Starchaser::State;
  switch (starchaser.state) {
    case State::None:
      starchaser.state = State::Collecting;
      break;

    case State::Collecting:
      CollectStar(ett_mgr, eid);
      break;

    case State::Selling:
      SellStar(ett_mgr, eid);
      break;

    case State::GoingHome:
      GoHome(ett_mgr, eid);
      break;

    case State::Resting:
      Rest(ett_mgr, eid);
      break;

    default:
      break;
  }
}  // namespace sys

}  // namespace sys
}  // namespace astar
