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

void FlushCellBuffer(const sgl::WorldState& world_state,
                     CellBuffer& cell_buffer, float sense_radius,
                     glm::vec2 pos) {
  auto top_left = pos - glm::vec2(sense_radius, sense_radius);
  auto tl_coords = GetCoordsInGrid(world_state, top_left);
  auto button_right = pos + glm::vec2(sense_radius, sense_radius);
  auto br_coords = GetCoordsInGrid(world_state, button_right);
  auto buffer_size = br_coords - tl_coords;
  buffer_size += glm::uvec2(1, 1);

  cell_buffer.resize(static_cast<std::size_t>(buffer_size.x) * buffer_size.y);
  const auto& grid = world_state.grid;
  grid.GetCells(tl_coords.x, tl_coords.y, buffer_size.x, buffer_size.y,
                cell_buffer.data());
}

bool IsRelevant(const AgentInfo& agent_info, const glm::vec2& pos,
                const cmp::Sense& sense_comp, einu::EID eid) {
  using namespace einu::util;  // NOLINT
  if (eid == agent_info.eid) return false;
  if ((agent_info.type & sense_comp.relevant_type_signature) ==
      agent_info.type) {
    auto dist2 = glm::distance2(pos, agent_info.pos);
    bool within_sense_range = dist2 < glm::pow(sense_comp.sense_radius, 2);
    if (within_sense_range) {
      return true;
    }
  }
  return false;
}

void Sense(const sgl::WorldState& world_state, CellBuffer& cell_buffer,
           cmp::Sense& sense, const einu::common::cmp::Transform& transform,
           cmp::Memory& memory, einu::EID eid) {
  cell_buffer.clear();
  FlushCellBuffer(world_state, cell_buffer, sense.sense_radius,
                  transform.GetPosition());
  auto&& mem = memory.memory;
  mem.clear();
  for (auto&& cell : cell_buffer) {
    for (auto&& agent_info : *cell) {
      if (IsRelevant(agent_info, transform.GetPosition(), sense, eid)) {
        mem.emplace_back(agent_info);
      }
    }
  }
}

void Forget(cmp::Memory& memory) { memory.memory.clear(); }

}  // namespace sys
}  // namespace lol
