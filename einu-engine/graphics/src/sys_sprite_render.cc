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

#include "einu-engine/graphics/sys_sprite_render.h"

#include <glad/glad.h>

namespace einu {
namespace graphics {
namespace sys {

void InitSpriteBatch(sgl::SpriteBatch& spite_batch, ResourceID vao,
                     ResourceID quad_vbo, ResourceID instance_vbo) {
  spite_batch.vao = vao;
  spite_batch.quad_vbo = quad_vbo;
  spite_batch.instance_vbo = instance_vbo;
}

void PrepareSpriteBatch(sgl::SpriteBatch& sprite_batch,
                        const cmp::Sprite& sprite,
                        const common::cmp::Transform& transform) {
  // TODO(Xiaoyue Chen): better clearing
  sprite_batch.sprite_table.clear();

  sprite_batch.sprite_table[sprite.shader][sprite.texture][sprite.quad]
      .emplace_back(sgl::SpriteBatch::Attribs{transform.GetTransform(),
                                              sprite.color, sprite.tex_coords});
}

void RenderSpriteBatch(const sgl::SpriteBatch& sprite_batch, glm::mat4 cam) {
  // TODO(Xiaoyue Chen): refactor these ugly code
  glBindVertexArray(sprite_batch.vao);
  glBindBuffer(GL_ARRAY_BUFFER, sprite_batch.quad_vbo);
  for (auto&& same_shader_sprites : sprite_batch.sprite_table) {
    auto shader = same_shader_sprites.first;
    glUseProgram(shader);
    auto pos = glGetAttribLocation(shader, "a_pos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    auto inst_transform = glGetAttribLocation(shader, "a_inst_transform");
    glEnableVertexAttribArray(inst_transform);
    auto attribs_size = sizeof(sgl::SpriteBatch::Attribs);
    glVertexAttribPointer(inst_transform, attribs_size / sizeof(float),
                          GL_FLOAT, GL_FALSE, attribs_size, 0);
    glVertexAttribDivisor(inst_transform, 1);
    for (auto&& same_tex_sprites : same_shader_sprites.second) {
      glBindTexture(GL_TEXTURE_2D, same_tex_sprites.first);
      for (auto&& same_quad_sprites : same_tex_sprites.second) {
        auto&& quad = same_tex_sprites.first;
        auto&& attribs_arr = same_quad_sprites.second;
        glBufferData(sprite_batch.quad_vbo, sizeof(Quad), &quad,
                     GL_STATIC_DRAW);
        glBufferData(sprite_batch.instance_vbo,
                     attribs_arr.size() * sizeof(sgl::SpriteBatch::Attribs),
                     attribs_arr.data(), GL_STATIC_DRAW);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, attribs_arr.size());
      }
    }
  }
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
