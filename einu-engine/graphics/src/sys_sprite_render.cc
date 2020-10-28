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

#include <glm/gtc/type_ptr.hpp>

namespace einu {
namespace graphics {
namespace sys {

void InitSpriteBatch(sgl::GLResourceTable& resource_table,
                     sgl::SpriteBatch& spite_batch, const char* vao,
                     const char* quad_vbo, const char* instance_vbo,
                     const char* sampler) {
  using Key = sgl::GLResourceTable::Key;
  spite_batch.vao =
      resource_table.table.at(Key{ResourceType::VertexArray, vao});
  spite_batch.quad_vbo =
      resource_table.table.at(Key{ResourceType::VertexBuffer, quad_vbo});
  spite_batch.instance_vbo =
      resource_table.table.at(Key{ResourceType::VertexBuffer, instance_vbo});
  spite_batch.sampler =
      resource_table.table.at(Key{ResourceType::Sampler, sampler});
}

void PrepareSpriteBatch(sgl::GLResourceTable& resource_table,
                        sgl::SpriteBatch& sprite_batch,
                        const cmp::Sprite& sprite,
                        const einu::cmp::Transform& transform) {
  using Key = sgl::GLResourceTable::Key;
  auto& sprite_rsc = resource_table.sprite_table.at(sprite.sprite_name);
  auto shader = resource_table.table.at(
      Key{ResourceType::ShaderProgram, sprite_rsc.shader});
  auto texture =
      resource_table.table.at(Key{ResourceType::Texture, sprite_rsc.texture});
  auto& sprite_data = sprite_batch.sprite_table[sprite.sprite_name];
  sprite_data.shader = shader;
  sprite_data.texture = texture;
  sprite_data.verts = sprite_rsc.verts;
  sprite_data.attibs_arr.emplace_back(
      sgl::SpriteBatch::Attribs{transform.GetTransform(), sprite.color});
}

void ClearSpriteBatch(sgl::SpriteBatch& sprite_batch) {
  for (auto&& pair : sprite_batch.sprite_table) {
    auto& sprite_data = pair.second;
    sprite_data.attibs_arr.clear();
  }
}

void SetupUniform(ResourceID shader, const glm::mat4& cam) {
  auto camera = glGetUniformLocation(shader, "u_camera");
  glUniformMatrix4fv(camera, 1, GL_FALSE, glm::value_ptr(cam));
}

void SetupQuadAttribs(ResourceID shader, ResourceID quad_vbo,
                      const std::array<Vertex, 4>& verts) {
  std::array<Vertex, 6> verts6 = {
      verts[0], verts[1], verts[2],  // triangle 1
      verts[2], verts[3], verts[0],  // triangle 2
  };

  glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
  auto pos = glGetAttribLocation(shader, "a_pos");
  glEnableVertexAttribArray(pos);
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  auto color = glGetAttribLocation(shader, "a_color");
  glEnableVertexAttribArray(color);
  glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<const void*>(3 * sizeof(float)));
  auto tex_coords = glGetAttribLocation(shader, "a_tex_coords");
  glEnableVertexAttribArray(tex_coords);
  glVertexAttribPointer(tex_coords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<const void*>(7 * sizeof(float)));
  glBufferData(GL_ARRAY_BUFFER, verts6.size() * sizeof(Vertex), &verts6,
               GL_STATIC_DRAW);
}

void SetupInstanceAttribs(ResourceID shader, ResourceID inst_vbo,
                          const sgl::SpriteBatch::AttribsArr& attrib_arr) {
  glBindBuffer(GL_ARRAY_BUFFER, inst_vbo);
  auto inst_transform = glGetAttribLocation(shader, "a_inst_transform");
  auto attribs_size = sizeof(sgl::SpriteBatch::Attribs);
  for (std::size_t i = 0; i != 4; ++i) {
    auto loc = inst_transform + i;
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, attribs_size,
                          reinterpret_cast<const void*>(i * 4 * sizeof(float)));
    glVertexAttribDivisor(loc, 1);
  }

  auto inst_color = glGetAttribLocation(shader, "a_inst_color");
  glEnableVertexAttribArray(inst_color);
  glVertexAttribPointer(inst_color, 4, GL_FLOAT, GL_FALSE, attribs_size,
                        reinterpret_cast<const void*>(16 * sizeof(float)));
  glVertexAttribDivisor(inst_color, 1);

  glBufferData(GL_ARRAY_BUFFER,
               attrib_arr.size() * sizeof(sgl::SpriteBatch::AttribsArr),
               attrib_arr.data(), GL_STATIC_DRAW);
}

void RenderSpriteBatch(const sgl::SpriteBatch& sprite_batch,
                       const glm::mat4& cam) {
  auto sampler = sprite_batch.sampler;
  glBindSampler(0, sampler);
  glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glEnable(GL_DEPTH_TEST);

  for (auto&& pair : sprite_batch.sprite_table) {
    auto&& sprite_data = pair.second;
    auto shader = sprite_data.shader;
    glUseProgram(shader);
    glBindVertexArray(sprite_batch.vao);
    glBindTexture(GL_TEXTURE_2D, sprite_data.texture);
    SetupUniform(shader, cam);
    SetupQuadAttribs(shader, sprite_batch.quad_vbo, sprite_data.verts);
    SetupInstanceAttribs(shader, sprite_batch.instance_vbo,
                         sprite_data.attibs_arr);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, sprite_data.attibs_arr.size());
  }
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
