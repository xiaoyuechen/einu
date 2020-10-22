#include "einu-window/window_sys.h"

#include <GLFW/glfw3.h>

#include <cassert>
#include <stdexcept>

namespace einu {
namespace window {
namespace sys {

namespace {

void SetWindowHint(const comp::Window& window) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, window.sample);
  if (window.mode == comp::Window::Mode::kWindowedFullScreen) {
    int count;
    auto monitors = glfwGetMonitors(&count);
    if (window.monitor_index + 1 < count) {
      throw std::runtime_error("not enough monitors");
    }
    auto monitor = monitors[window.monitor_index];
    auto mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  }
}

GLFWmonitor* GetMonitorArgument(const comp::Window& window) {
  switch (window.mode) {
    case comp::Window::Mode::kWindowedFullScreen:
    case comp::Window::Mode::kFullScreen: {
      int count;
      auto monitors = glfwGetMonitors(&count);
      if (window.monitor_index + 1 < count) {
        throw std::runtime_error("not enough monitors");
      }
      auto monitor = monitors[window.monitor_index];
      return monitor;
    }
    case comp::Window::Mode::kWindowed:
      return nullptr;
    default:
      break;
  }
  return nullptr;
}

}  // namespace

void Create(comp::Window& window) {
  SetWindowHint(window);
  auto glfw_win = glfwCreateWindow(window.size.width, window.size.height,
                                   window.title.c_str(),
                                   GetMonitorArgument(window), nullptr);
  if (!glfw_win) {
    throw std::runtime_error("failed to create window " + window.title);
  }
  window.window = glfw_win;
  glfwSetWindowUserPointer(glfw_win, &window);
  glfwMakeContextCurrent(glfw_win);
}

}  // namespace sys
}  // namespace window
}  // namespace einu