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

#include "einu-engine/common/cmp_movement.h"
#include "einu-engine/common/cmp_transform.h"
#include "einu-engine/core/i_entity_manager.h"
#include "src/cmp.h"
#include "src/sgl_world_state.h"

namespace astar {
namespace sys {

void MoveAlongPath(const sgl::WorldState& world_state,
                   const einu::cmp::Transform& transform,
                   einu::cmp::Movement& movement,
                   cmp::PathFinding& path_finding);

void RunStarChaserFSM(einu::IEntityManager& ett_mgr, einu::EID eid);

}  // namespace sys
}  // namespace astar
