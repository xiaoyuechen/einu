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

#include "src/sys_cell.h"

namespace astar {
namespace sys {

void UpdateCell(const sgl::WorldState& world_state, const cmp::Cell& cell,
                einu::graphics::cmp::Sprite& sprite) {
  auto& c = world_state.grid[cell.pos.x][cell.pos.y];
  if (c.state == CellState::Clear) {
    sprite.color.a = 0;
  } else {
    sprite.color.a = 255;
  }
}

}  // namespace sys
}  // namespace astar
