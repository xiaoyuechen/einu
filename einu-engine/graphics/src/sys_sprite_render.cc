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

namespace einu {
namespace graphics {
namespace sys {

void PrepareSpriteBatch(sgl::SpriteBatch& sprite_batch,
                        const cmp::Sprite& sprite,
                        const common::cmp::Transform& transform) {
  // TODO(Xiaoyue Chen): better clearing
  sprite_batch.sprite_table.clear();

  sprite_batch.sprite_table[sprite.shader][sprite.texture][sprite.quad]
      .emplace_back(sgl::SpriteBatch::Attribs{transform.GetTransform(),
                                              sprite.color, sprite.tex_coords});
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
