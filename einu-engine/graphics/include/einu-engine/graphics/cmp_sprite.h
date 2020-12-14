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

#include <string>

#include "einu-engine/core/xnent.h"
#include "einu-engine/graphics/resource.h"
#include "glm/glm.hpp"

namespace einu {
namespace graphics {
namespace cmp {

struct Sprite : public Xnent {
  std::string sprite_name;
  glm::vec4 color = glm::vec4{255, 255, 255, 255};
};

}  // namespace cmp
}  // namespace graphics
}  // namespace einu
