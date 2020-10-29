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
#include <array>
#include <vector>

namespace astar {
namespace sys {

bool IsValid(glm::uvec2 grid_size, glm::ivec2 pos) {
  if (pos.x < 0) return false;
  if (pos.y < 0) return false;
  if (pos.x >= static_cast<int>(grid_size.x)) return false;
  if (pos.y >= static_cast<int>(grid_size.y)) return false;
  return true;
}

std::vector<glm::uvec2> FindNeighbours(const sgl::WorldState::Grid& grid,
                                       glm::uvec2 pos) {
  auto neighbours = std::vector<glm::uvec2>{};
  auto ipos = glm::ivec2(pos);
  auto xs = std::array<int, 3>{-1, 0, 1};
  auto ys = std::array<int, 3>{-1, 0, 1};
  auto grid_size = grid.GetSize();
  for (auto x : xs) {
    for (auto y : ys) {
      if (!(x == 0 && y == 0)) {
        auto neighbour = ipos + glm::ivec2(x, y);
        if (IsValid(grid_size, neighbour)) {
          neighbours.push_back(glm::uvec2(neighbour));
        }
      }
    }
  }
  return neighbours;
}

void ConstructPath(cmp::PathFinding& path_finding,
                   cmp::PathFinding::Node last) {
  for (cmp::PathFinding::Node* node = &last; node != nullptr;
       node = node->parent) {
    path_finding.path.push_back(node->pos);
  }
}

void FindPathImpl(sgl::WorldState& world_state,
                  cmp::PathFinding& path_finding) {
  if (path_finding.open_list.size() == 0) {
    return;
  }
  using Node = cmp::PathFinding::Node;
  auto current_it = std::min_element(
      path_finding.open_list.begin(), path_finding.open_list.end(),
      [](auto&& lfs, auto&& rfs) { return lfs.f < rfs.f; });

  path_finding.closed_list.push_back(*current_it);
  path_finding.open_list.erase(current_it);
  auto& current = path_finding.closed_list.back();
  if (current.pos == path_finding.destination) {
    ConstructPath(path_finding, current);
    return;
  }

  auto neighbours_pos = FindNeighbours(world_state.grid, current.pos);
  for (auto&& neighbour_pos : neighbours_pos) {
    auto neighbour = Node{neighbour_pos, &current};
    if (world_state.grid[neighbour.pos.x][neighbour.pos.y].state ==
        CellState::Blocked) {
      continue;
    }

    if (std::find_if(path_finding.closed_list.begin(),
                     path_finding.closed_list.end(), [=](auto&& node) {
                       return node.pos == neighbour.pos;
                     }) != path_finding.closed_list.end()) {
      continue;
    }

    neighbour.g = current.g + glm::distance(glm::vec2(current.pos),
                                            glm::vec2(neighbour.pos));
    neighbour.h = glm::distance(glm::vec2(neighbour.pos),
                                glm::vec2(path_finding.destination));
    neighbour.f = neighbour.g + neighbour.h;

    auto neighbour_in_open = std::find_if(
        path_finding.open_list.begin(), path_finding.open_list.end(),
        [=](auto&& node) { return node.pos == neighbour.pos; });
    if (neighbour_in_open == path_finding.open_list.end()) {
      path_finding.open_list.push_back(neighbour);
    } else if (neighbour.f < neighbour_in_open->f) {
      *neighbour_in_open = neighbour;
    }
  }

  FindPathImpl(world_state, path_finding);
}

void FindPath(sgl::WorldState& world_state, cmp::PathFinding& path_finding,
              glm::vec2 start, glm::vec2 dest) {
  using Node = cmp::PathFinding::Node;
  path_finding.start = sgl::GetCoordsInGrid(world_state, start);
  path_finding.destination = sgl::GetCoordsInGrid(world_state, dest);

  path_finding.open_list.clear();
  path_finding.open_list.reserve(world_state.grid.GetTotalCellCount() * 2);
  path_finding.closed_list.clear();
  path_finding.closed_list.reserve(world_state.grid.GetTotalCellCount() * 2);

  auto start_node = Node(path_finding.start, nullptr);
  start_node.pos = sgl::GetCoordsInGrid(world_state, start);
  path_finding.open_list.push_back(start_node);

  FindPathImpl(world_state, path_finding);
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
