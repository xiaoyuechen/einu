#include "ecs-engine/window/gl_creater.h"

#include <GLFW/glfw3.h>

#include "ecs-engine/graphics/gl_error.h"

namespace ecs {
namespace window {

void* GLCreater::CreateWindow() const {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hint_.major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hint_.minor);
  GLFWmonitor* monitor =
      setting_.mode == Mode::kFullScreen ? glfwGetPrimaryMonitor() : nullptr;
  GLFWwindow* window =
      glfwCreateWindow(setting_.width, setting_.height, setting_.title.c_str(),
                       monitor, nullptr);
  if (!window) {
    throw GLError("can't create window");
  }
  return window;
}

}  // namespace window
}  // namespace ecs