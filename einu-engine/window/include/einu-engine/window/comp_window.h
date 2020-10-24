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

#include <einu-engine/core/xnent.h>

#include <cstddef>
#include <string>

#include "einu-engine/window/input.h"

struct GLFWwindow;

namespace einu {
namespace window {
namespace comp {

struct Window : public Xnent {
  enum class Mode {
    Windowed,
    FullScreen,
    WindowedFullScreen,
  };

  struct Size {
    int width, height;
  };

  Mode mode = Mode::Windowed;
  Size size = {1280, 720};
  std::string title = "default title";
  std::size_t monitor_index = 0;
  int swap_interval = 1;
  int sample = 4;
  bool shouldClose = false;
  Size frame_size = {};
  GLFWwindow* window = nullptr;
  input::InputBuffer input_buffer;
};

}  // namespace comp
}  // namespace window
}  // namespace einu
