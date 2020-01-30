#include "ecs-engine/window/window.h"

#include "ecs-engine/graphics/gl_error.h"

namespace ecs {

Window::Window(Mode mode, int width, int height, const char* title)
    : window_([=]() -> GLFWwindow& {
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
      glfwSwapInterval(1);
      return *window;
    }()) {}

Window::~Window() { glfwDestroyWindow(&window_); }

void Window::SetKeyCallback(const input::KeyCallback& key_callback) {
  using namespace input;
  static const auto copy = key_callback;
  auto callback = []([[maybe_unused]] GLFWwindow* window,
                     int key,
                     [[maybe_unused]] int scancode,
                     int action,
                     int mods) {
    copy(static_cast<KeyboardKey>(key),
         static_cast<Action>(action),
         static_cast<ModifierKey>(mods));
  };
  glfwSetKeyCallback(&window_, callback);
}

}  // namespace ecs