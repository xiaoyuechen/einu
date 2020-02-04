#ifndef INPUT_FN_H_
#define INPUT_FN_H_

#include <functional>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ecs-engine/input/input.h"

namespace ecs {

class Window;

namespace input {

template <typename... FnArgs>
class InputFn {
 public:
  using Fn = std::function<void(FnArgs...)>;
  InputFn() = default;
  explicit InputFn(const Fn& fn);

 protected:
  Fn fn_;
};

class KeyFn : public InputFn<Window&, KeyboardKey, Action, ModifierKey> {
 public:
  using InputFn::InputFn;
  static void Invoke(
      GLFWwindow* win, int key, int scancode, int action, int mods);
};

class MouseButtonFn
    : public InputFn<Window&, MouseButton, Action, ModifierKey> {
 public:
  using InputFn::InputFn;
  static void Invoke(GLFWwindow* win, int button, int action, int mods);
};

class ScrollFn : public InputFn<Window&, double, double> {
 public:
  using InputFn::InputFn;
  static void Invoke(GLFWwindow* win, double xoffset, double yoffset);
};

class CursorPosFn : public InputFn<Window&, double, double> {
 public:
  using InputFn::InputFn;
  static void Invoke(GLFWwindow* win, double xpos, double ypos);
};

//////////////////////////////////////////////////////////////////////////

template <typename... FnArgs>
inline InputFn<FnArgs...>::InputFn(const Fn& fn)
    : fn_(fn) {}

}  // namespace input

}  // namespace ecs

#endif  // INPUT_FN_H_
