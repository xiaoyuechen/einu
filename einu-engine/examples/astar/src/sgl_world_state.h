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

#include <einu-engine/common/grid.h>
#include <einu-engine/core/eid.h>
#include <einu-engine/core/xnent.h>

#include <algorithm>
#include <glm/glm.hpp>
#include <vector>

#include "src/cell.h"

namespace astar {
namespace sgl {

struct WorldState : public einu::Xnent {
  using Grid = einu::Grid<Cell>;

  Grid grid{};
  glm::vec2 world_size{};
  glm::vec2 trading_post_pos;
  glm::vec2 space_ship_pos;
  glm::vec2 star_pos;
};

inline glm::vec2 GetCellSize(const WorldState& world_state) noexcept {
  return world_state.world_size / glm::vec2(world_state.grid.GetSize());
}

inline glm::uvec2 GetCoordsInGrid(const sgl::WorldState& world_state,
                                  const glm::vec2& pos) {
  auto san_pos = pos;
  for (int i = 0; i != san_pos.length(); ++i) {
    if (san_pos[i] < 0) {
      san_pos[i] = 0;
    }
  }
  auto cell_size = GetCellSize(world_state);
  auto grid_size = world_state.grid.GetSize();
  auto coords = static_cast<glm::uvec2>(san_pos / cell_size);
  for (int i = 0; i != coords.length(); ++i) {
    auto& val = coords[i];
    val = std::clamp(val, 0u, grid_size[i] - 1);
  }
  return coords;
}

}  // namespace sgl
}  // namespace astar
