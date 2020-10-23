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