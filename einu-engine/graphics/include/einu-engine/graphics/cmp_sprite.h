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

#include <einu-engine/common/transform.h>
#include <einu-engine/core/xnent.h>

#include <cstdint>

#include "einu-engine/graphics/quat.h"
#include "einu-engine/graphics/resource.h"

namespace einu {
namespace graphics {
namespace cmp {

struct Sprite : public Xnent {
  ResourceID texture = ~ResourceID{0};
  glm::vec4 color;
  glm::vec2 tex_coords;
  Quad quad;
};

}  // namespace cmp
}  // namespace graphics
}  // namespace einu
