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

#include <einu-engine/common/cmp_transform.h>

#include <vector>

#include "src/cmp_agent.h"
#include "src/sgl_world_state.h"

namespace lol {
namespace sys {

using CellBuffer = std::vector<const sgl::WorldState::Cell*>;

void Sense(const sgl::WorldState& world_state, CellBuffer& cell_buffer,
           cmp::Sense& sense, const einu::common::cmp::Transform& transform,
           cmp::Memory& memory, einu::EID eid);

}  // namespace sys
}  // namespace lol
