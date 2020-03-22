#include "ecs-engine/window/window.h"

#include "ecs-engine/graphics/gl_error.h"
#include "glad/glad.h"

namespace ecs {

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

Window::Window(Mode mode, int width, int height, const char* title)
    : window_([=]() -> GLFWwindow& {
      InitializeGLFW();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      GLFWmonitor* monitor =
          mode == Mode::FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr;
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

Window::~Window() {
  glfwDestroyWindow(&window_);
  glfwTerminate();
}

void Window::SetWindowShouldClose(bool should_close) {
  glfwSetWindowShouldClose(&window_, should_close);
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(&window_); }

void Window::SwapBuffer() { glfwSwapBuffers(&window_); }

void Window::PollEvents() { glfwPollEvents(); }

double Window::GetTime() const { return glfwGetTime(); }

void Window::SetTime(double time) { glfwSetTime(time); }

void Window::SetInputCallback(tmp::Type2Type<input::KeyFn>,
                              GLFWkeyfun callback) {
  glfwSetKeyCallback(&window_, callback);
}

void Window::SetInputCallback(tmp::Type2Type<input::MouseButtonFn>,
                              GLFWmousebuttonfun callback) {
  glfwSetMouseButtonCallback(&window_, callback);
}

void Window::SetInputCallback(tmp::Type2Type<input::ScrollFn>,
                              GLFWscrollfun callback) {
  glfwSetScrollCallback(&window_, callback);
}

void Window::SetInputCallback(tmp::Type2Type<input::CursorPosFn>,
                              GLFWcursorposfun callback) {
  glfwSetCursorPosCallback(&window_, callback);
}

}  // namespace ecs