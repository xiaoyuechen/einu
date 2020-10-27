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
#include <cstdint>
#include <glm/glm.hpp>
#include <string>

#include "einu-engine/graphics/vertex.h"

namespace einu {
namespace graphics {

using ResourceID = std::uint32_t;

enum class ResourceType {
  VertexArray,
  VertexBuffer,
  VertexShader,
  FragmentShader,
  ShaderProgram,
  Texture,
  Sampler,
  Count
};

struct TextureInfo {
  glm::i32vec2 size;
};

struct Sprite {
  std::string shader;
  std::string texture;

  // verts order
  // 3  ------ 2
  //   |      |
  // 0  ------ 1
  std::array<Vertex, 4> verts;
};

}  // namespace graphics
}  // namespace einu
