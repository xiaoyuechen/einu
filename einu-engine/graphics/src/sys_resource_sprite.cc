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

#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

void CreateSprite(sgl::GLResourceTable& resource_table, const char* name,
                  const char* shader_name, const char* tex_name) {
  auto& tex_info = resource_table.tex_info_table.at(tex_name);
  auto& tex_size = tex_info.size;
  auto& sprite = resource_table.sprite_table[name];
  sprite.shader = shader_name;
  sprite.texture = tex_name;
  auto& verts = sprite.verts;
  verts[0].pos = glm::vec3(0, 0, 0);
  verts[1].pos = verts[0].pos + glm::vec3(tex_size.x, 0, 0);
  verts[2].pos = verts[1].pos + glm::vec3(0, tex_size.y, 0);
  verts[3].pos = verts[0].pos + glm::vec3(0, tex_size.y, 0);

  for (auto&& vert : verts) {
    vert.color = glm::vec3(255, 255, 255);
    vert.uv = glm::vec2(vert.pos) / glm::vec2(tex_size);
  }
}

// TODO(Xiaoyue Chen): implement this function
void DestroySprite(sgl::GLResourceTable& resource_table, const char* name) {}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
