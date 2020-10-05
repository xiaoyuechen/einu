#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace einu {
namespace system {
class IntializeGlfw {
 public:
  void Init() { glfwInit(); }
};
}  // namespace system
}  // namespace einu