#pragma once

#include <string>

#include "einu-engine/core/i_component.h"

namespace einu {
namespace comp {

struct Window : public IComponent {
  enum class Mode {
    kWindowed,
    kFullScreen,
    kWindowedFullScreen,
  };

  struct Size {
    int width, height;
  };

  Mode mode = Mode::kWindowed;
  Size size = {0, 0};
  std::string title = "";
  std::size_t monitor_index = 0;
  int sample = 4;
  bool shouldClose = false;
  void* window = nullptr;
};

}  // namespace comp
}  // namespace einu
