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

#include <glad/glad.h>

#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

template <>
void Create<ResourceType::VertexBuffer>(sgl::GLResourceTable& resource_table,
                                        const char* name) {
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);

  using Key = sgl::GLResourceTable::Key;
  resource_table.table.emplace(Key{ResourceType::VertexBuffer, name},
                               vertex_buffer);
}

template <>
void Destroy<ResourceType::VertexBuffer>(sgl::GLResourceTable& resource_table,
                                         const char* name) {
  using Key = sgl::GLResourceTable::Key;
  auto it = resource_table.table.find(Key{ResourceType::VertexBuffer, name});
  glDeleteBuffers(1, &it->second);
  resource_table.table.erase(it);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
