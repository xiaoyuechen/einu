#include "ecs-engine/window/gl_closer.h"


namespace ecs {
namespace window {

namespace {
GLFWwindow* GetGlWindow(void* window) noexcept {
  return static_cast<GLFWwindow*>(window);
}
}  // namespace

void GLCloser::SetShouldClose(bool should_close) {
  glfwSetWindowShouldClose(GetGlWindow(window_), should_close);
}

bool GLCloser::ShouldClose() const {
  return glfwWindowShouldClose(GetGlWindow(window_));
}

}  // namespace window
}  // namespace ecs