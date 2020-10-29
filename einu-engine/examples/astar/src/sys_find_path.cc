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

#include "src/sys_find_path.h"

#include <einu-engine/graphics/cmp_sprite.h>

#include <algorithm>

namespace astar {
namespace sys {

void FindPathImpl(sgl::WorldState& world_state,
                  cmp::PathFinding& path_finding) {
  if (path_finding.open_list.size() == 0) {
    return;
  }
  using Node = cmp::PathFinding::Node;
  auto least_f_node_it = std::min_element(
      path_finding.open_list.begin(), path_finding.open_list.end(),
      [](auto&& lfs, auto&& rfs) { return lfs.f < rfs.f; });

  auto least_f_node = Node{*least_f_node_it};
  path_finding.open_list.erase(least_f_node_it);
}

void FindPath(sgl::WorldState& world_state, cmp::PathFinding& path_finding,
              glm::vec2 start, glm::vec2 dest) {
  using Node = cmp::PathFinding::Node;
  path_finding.open_list.clear();
  path_finding.closed_list.clear();
  auto start_node = Node{sgl::GetCoordsInGrid(world_state, start)};
  auto dest_node = Node{sgl::GetCoordsInGrid(world_state, dest)};
  path_finding.open_list.push_back(start_node);
  path_finding.destination = dest_node;
}

void RenderPath(einu::IEntityManager& ett_mgr,
                const cmp::PathFinding& path_finding) {
  const auto& world_state = ett_mgr.GetSinglenent<sgl::WorldState>();
  for (auto&& pos : path_finding.path) {
    auto node = world_state.grid[pos.x][pos.y];
    auto& sprite = ett_mgr.GetComponent<einu::graphics::cmp::Sprite>(node.eid);
    sprite.color = glm::vec4{255, 0, 0, 255};
  }
}

}  // namespace sys
}  // namespace astar
