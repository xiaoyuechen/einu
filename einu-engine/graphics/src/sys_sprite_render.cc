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

  // sprite_batch.sprite_table[sprite.shader][sprite.texture][sprite.rect]
  //    .emplace_back(sgl::SpriteBatch::Attribs{transform.GetTransform(),
  //                                            sprite.color,
  //                                            sprite.tex_coords});
}

void RenderSpriteBatch(const sgl::SpriteBatch& sprite_batch, glm::mat4 cam) {
  // TODO(Xiaoyue Chen): refactor these ugly code
  glBindVertexArray(sprite_batch.vao);
  for (auto&& same_shader_sprites : sprite_batch.sprite_table) {
    auto shader = same_shader_sprites.first;
    glUseProgram(shader);
    auto camera = glGetUniformLocation(shader, "u_camera");
    glUniformMatrix4fv(camera, 1, GL_FALSE, &cam[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, sprite_batch.quad_vbo);
    auto pos = glGetAttribLocation(shader, "a_pos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, sprite_batch.instance_vbo);
    auto inst_transform = glGetAttribLocation(shader, "a_inst_transform");
    auto attribs_size = sizeof(sgl::SpriteBatch::Attribs);
    for (std::size_t i = 0; i != 4; ++i) {
      auto loc = inst_transform + i;
      glEnableVertexAttribArray(loc + i);
      glVertexAttribPointer(
          loc, 4, GL_FLOAT, GL_FALSE, attribs_size,
          reinterpret_cast<const void*>(i * 4 * sizeof(float)));
      glVertexAttribDivisor(loc, 1);
    }

    auto inst_color = glGetAttribLocation(shader, "a_inst_color");
    glEnableVertexAttribArray(inst_color);
    glVertexAttribPointer(inst_color, 4, GL_FLOAT, GL_FALSE, attribs_size,
                          reinterpret_cast<const void*>(16 * sizeof(float)));
    glVertexAttribDivisor(inst_color, 1);

    auto inst_tex_coords = glGetAttribLocation(shader, "a_inst_tex_coords");
    glEnableVertexAttribArray(inst_tex_coords);
    glVertexAttribPointer(inst_tex_coords, 2, GL_FLOAT, GL_FALSE, attribs_size,
                          reinterpret_cast<const void*>(20 * sizeof(float)));
    glVertexAttribDivisor(inst_tex_coords, 1);

    for (auto&& same_tex_sprites : same_shader_sprites.second) {
      glBindTexture(GL_TEXTURE_2D, same_tex_sprites.first);
      for (auto&& same_quad_sprites : same_tex_sprites.second) {
        auto&& quad = same_quad_sprites.first;
        auto&& attribs_arr = same_quad_sprites.second;
        glBindBuffer(GL_ARRAY_BUFFER, sprite_batch.quad_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, sprite_batch.instance_vbo);
        glBufferData(GL_ARRAY_BUFFER,
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
