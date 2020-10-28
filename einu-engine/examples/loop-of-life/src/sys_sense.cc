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

#include "src/sys_sense.h"

namespace lol {
namespace sys {

// void FlushCellBuffer(const cmp::Sense& sense_comp,
//                     const ecs::TransformComponent& transform_comp) {
//  auto sense_radius = sense_comp.sense_radius;
//  auto pos = glm::vec2(transform_comp.transform.GetPosition());
//  auto top_left = pos - glm::vec2(sense_radius, sense_radius);
//  auto tl_coords = world_util::GetCoordsInGrid(world_setting_, top_left);
//  auto button_right = pos + glm::vec2(sense_radius, sense_radius);
//  auto br_coords = world_util::GetCoordsInGrid(world_setting_, button_right);
//  auto buffer_size = br_coords - tl_coords;
//  buffer_size += glm::uvec2(1, 1);
//
//  cell_buffer_.resize(static_cast<std::size_t>(buffer_size.x) *
//  buffer_size.y); const auto& grid = world_state_.grid;
//  grid.GetCells(tl_coords.x, tl_coords.y, buffer_size.x, buffer_size.y,
//                cell_buffer_.data());
//}

void Sense(const sgl::WorldState& world_state,
           const einu::common::cmp::Transform& transform, cmp::Memory& memory) {
}

}  // namespace sys
}  // namespace lol
