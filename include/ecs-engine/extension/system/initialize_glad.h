#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>

namespace einu {
namespace system {
class InitializeGlad {
 public:
  void Init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw std::runtime_error("failed to init glad");
    }
  }
};
}  // namespace system
}  // namespace einu