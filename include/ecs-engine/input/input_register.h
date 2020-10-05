#pragma once

#include "einu-engine/input/input.h"
#include "einu-engine/input/input_fn.h"

namespace einu {
namespace input {

class InputRegister {
 public:
  InputRegister(window::Window& window)
      : window_(window) {}

  void RegisterCallback(const input::KeyFn& callback);
  void RegisterCallback(const input::MouseButton& callback);
  void RegisterCallback(const input::ScrollFn& callback);
  void RegisterCallback(const input::CursorPosFn& callback);

 private:
  window::GLWindow& window_;
};

}  // namespace input
}  // namespace einu