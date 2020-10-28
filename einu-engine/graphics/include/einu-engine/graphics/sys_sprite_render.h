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

#include "einu-engine/graphics/cmp_camera.h"
#include "einu-engine/graphics/cmp_sprite.h"
#include "einu-engine/graphics/sgl_resource_table.h"
#include "einu-engine/graphics/sgl_sprite_batch.h"

namespace einu {
namespace graphics {
namespace sys {

void InitSpriteBatch(sgl::GLResourceTable& resource_table,
                     sgl::SpriteBatch& spite_batch, const char* vao,
                     const char* quad_vbo, const char* instance_vbo,
                     const char* sampler);

void PrepareSpriteBatch(sgl::GLResourceTable& resource_table,
                        sgl::SpriteBatch& sprite_batch,
                        const cmp::Sprite& sprite,
                        const einu::cmp::Transform& transform);

void ClearSpriteBatch(sgl::SpriteBatch& sprite_batch);

void RenderSpriteBatch(const sgl::SpriteBatch& sprite_batch,
                       const glm::mat4& cam);

void HelloTriangleInit();
void HelloTriangleRender();

}  // namespace sys
}  // namespace graphics
}  // namespace einu
