#include "ecs-engine/window/gl_window.h"

#include "ecs-engine/graphics/gl_error.h"

namespace ecs {
namespace window {

namespace {
void InitializeGLFW() {
  if (!glfwInit()) {
    throw GLError("could not initialize glfw");
  }
  glfwSetErrorCallback(GLErrorCallback);
}

void InitializeGLAD() {
  auto proc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
  if (!gladLoadGLLoader(proc)) {
    throw GLError("could not initialize glad");
  }
}
}  // namespace

GLWindow::GLWindow(Mode mode, int width, int height, const char* title)
    : window_([=]() -> GLFWwindow& {
      InitializeGLFW();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      GLFWmonitor* monitor =
          mode == Mode::kFullScreen ? glfwGetPrimaryMonitor() : nullptr;
      GLFWwindow* window =
          glfwCreateWindow(width, height, title, monitor, nullptr);
      if (!window) {
        throw GLError("could not create window");
      }
      glfwMakeContextCurrent(window);
      InitializeGLAD();
      glfwSwapInterval(1);
      glfwSetWindowUserPointer(window, this);
      return *window;
    }()) {}

GLWindow::~GLWindow() {
  glfwDestroyWindow(&window_);
  glfwTerminate();
}



void GLWindow::SwapBuffer() { glfwSwapBuffers(&window_); }

void GLWindow::PollEvents() { glfwPollEvents(); }



}  // namespace window
}  // namespace ecs