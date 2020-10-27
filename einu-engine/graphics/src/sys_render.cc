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

#include "einu-engine/graphics/sys_render.h"

#include <glad/glad.h>

#include <sstream>

#include "einu-engine/graphics/graphics_error.h"

namespace einu {
namespace graphics {
namespace sys {

namespace {
void PostGLCallCallback(const char* name, void* funcptr, int len_args, ...) {
  GLenum error_code;
  error_code = glad_glGetError();

  if (error_code != GL_NO_ERROR) {
    auto buffer = std::stringstream{};
    buffer << "ERROR 0x" << std::hex << error_code << " in " << name;
    throw GraphicsError{std::move(buffer.str())};
  }
}
}  // namespace

void LoadGL() {
  if (!gladLoadGLLoader(
          reinterpret_cast<GLADloadproc>(window::GetProcAddress))) {
    throw GraphicsError{"Failed to load OpenGL"};
  }

#ifndef NDEBUG
  glad_set_post_callback(PostGLCallCallback);
#endif
}

void Clear() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
