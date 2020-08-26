#include "ecs-engine/input/input_register.h"

namespace ecs {
namespace input {

void KeyFn::Invoke(GLFWwindow* gl_win, int key, [[maybe_unused]] int scancode,
                   int action, int mods) {
  auto& win = GetWindow(gl_win);
  const auto& key_fn = win.GetInputCallback<KeyFn>();
  key_fn.fn_(win, static_cast<KeyboardKey>(key), static_cast<Action>(action),
             static_cast<ModifierKey>(mods));
}

void InputRegister::RegisterCallback(const input::KeyFn& callback) {
  static auto callback_static = callback;
  static auto callback_static = [](GLFWwindow* gl_win, int key,
                                   [[maybe_unused]] int scancode, int action,
                                   int mods) {

  }
}

void InputRegister::SetInputCallback(tmp::Type2Type<input::KeyFn>,
                                     GLFWkeyfun callback) {
  glfwSetKeyCallback(&window_, callback);
}

void InputRegister::SetInputCallback(tmp::Type2Type<input::MouseButtonFn>,
                                     GLFWmousebuttonfun callback) {
  glfwSetMouseButtonCallback(&window_, callback);
}

void InputRegister::SetInputCallback(tmp::Type2Type<input::ScrollFn>,
                                     GLFWscrollfun callback) {
  glfwSetScrollCallback(&window_, callback);
}

void InputRegister::SetInputCallback(tmp::Type2Type<input::CursorPosFn>,
                                     GLFWcursorposfun callback) {
  glfwSetCursorPosCallback(&window_, callback);
}

}  // namespace input
}  // namespace ecs