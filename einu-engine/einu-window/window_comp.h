#pragma once

#include <einu-core/xnent.h>

#include <cstddef>
#include <string>

#include "einu-window/input.h"

namespace einu {
namespace window {
namespace comp {

struct Window : public Xnent {
  enum class Mode {
    kWindowed,
    kFullScreen,
    kWindowedFullScreen,
  };

  struct Size {
    int width, height;
  };

  Mode mode = Mode::kWindowed;
  Size size = {1280, 720};
  std::string title = "default title";
  std::size_t monitor_index = 0;
  int sample = 4;
  bool shouldClose = false;
  struct GLFWwindow* window = nullptr;
  input::InputBuffer input_buffer;
};

}  // namespace comp
}  // namespace window
}  // namespace einu