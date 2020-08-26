#pragma once

#include <GLFW/glfw3.h>

namespace ecs {
namespace window {

struct GLInputCallbackStorage {
  GLFWkeyfun key;
  GLFWmousebuttonfun mouse_button;
  GLFWscrollfun scroll;
  GLFWcursorposfun cursor_pos;
};

}  // namespace window
}  // namespace ecs