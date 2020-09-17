#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace ecs {
namespace system {
class IntializeGlfw {
 public:
  void Init() { glfwInit(); }
};
}  // namespace system
}  // namespace ecs