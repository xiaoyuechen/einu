#pragma once

#include "ecs-engine/input/input.h"
#include "ecs-engine/input/input_fn.h"

namespace ecs {
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
}  // namespace ecs