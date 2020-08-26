#include "ecs-engine/input/input_fn.h"

#include "ecs-engine/window/gl_window.h"

namespace ecs {
namespace input {

namespace {
GLWindow& GetWindow(GLFWwindow* window) {
  return *static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
}
}  // namespace

void KeyFn::Invoke(GLFWwindow* gl_win,
                   int key,
                   [[maybe_unused]] int scancode,
                   int action,
                   int mods) {
  auto& win = GetWindow(gl_win);
  const auto& key_fn = win.GetInputCallback<KeyFn>();
  key_fn.fn_(win,
             static_cast<KeyboardKey>(key),
             static_cast<Action>(action),
             static_cast<ModifierKey>(mods));
}

void MouseButtonFn::Invoke(GLFWwindow* gl_win,
                           int button,
                           int action,
                           int mods) {
  auto& win = GetWindow(gl_win);
  const auto& fn = win.GetInputCallback<MouseButtonFn>();
  fn.fn_(win,
         static_cast<MouseButton>(button),
         static_cast<Action>(action),
         static_cast<ModifierKey>(mods));
}

void ScrollFn::Invoke(GLFWwindow* gl_win, double xoffset, double yoffset) {
  auto& win = GetWindow(gl_win);
  const auto& fn = win.GetInputCallback<ScrollFn>();
  fn.fn_(win, xoffset, yoffset);
}

void CursorPosFn::Invoke(GLFWwindow* gl_win, double xpos, double ypos) {
  auto& win = GetWindow(gl_win);
  const auto& fn = win.GetInputCallback<CursorPosFn>();
  fn.fn_(win, xpos, ypos);
}

}  // namespace input
}  // namespace ecs
