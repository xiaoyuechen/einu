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

#include <array>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "einu-engine/common/primitives.h"
#include "einu-engine/core/xnent.h"
#include "glm/glm.hpp"

namespace einu {
namespace graphics {
namespace sgl {

struct SpriteBatch : public Xnent {
  struct Attribs {
    glm::mat4 inst_transform;
    glm::vec4 inst_color;
  };

  using AttribsArr = std::vector<Attribs>;

  struct SpriteData {
    ResourceID shader;
    ResourceID texture;
    std::array<Vertex, 4> verts;
    AttribsArr attibs_arr;
  };

  absl::flat_hash_map<std::string, SpriteData> sprite_table;

  ResourceID vao;
  ResourceID quad_vbo;
  ResourceID instance_vbo;
  ResourceID sampler;
};

}  // namespace sgl
}  // namespace graphics
}  // namespace einu
