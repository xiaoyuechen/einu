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

#include "src/sys_world_state.h"

namespace lol {
namespace sys {

void UpdateWorldState(sgl::WorldState& world_state,
                      const einu::cmp::Transform& transform,
                      const cmp::Agent& agent, einu::EID eid) {
  const auto& pos = transform.GetPosition();
  auto grid_coords = GetCoordsInGrid(world_state, pos);
  auto& grid = world_state.grid;
  auto& cell_data = grid[grid_coords.y][grid_coords.x];
  cell_data.emplace_back(AgentInfo{agent.type, pos, eid});
}

void ClearWorldState(sgl::WorldState& world_state) noexcept {
  for (auto&& cell : world_state.grid) {
    cell.clear();
  }
}

}  // namespace sys
}  // namespace lol
