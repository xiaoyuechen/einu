#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <stdexcept>

#include "ecs-engine/core/system.h"
#include "ecs-engine/extension/component/entity_storage.h"
#include "ecs-engine/extension/component/window.h"
#include "ecs-engine/utility/iterator/zip.h"

namespace ecs {
namespace system {

template <typename EntityManager>
using CreateGlfwWindowComponentList =
    ComponentList<comp::Window, comp::EntityStorage<EntityManager>>;

template <typename EntityManager>
class CreateGlfwWindow
    : public System<EntityManager,
                    CreateGlfwWindowComponentList<EntityManager>> {
 public:
  using System =
      System<EntityManager, CreateGlfwWindowComponentList<EntityManager>>;
  using System::System;

  void Create() {
    System::RefreshMatchingBuffer();
    auto& matching_buffer = System::GetMatchingBuffer();
    for (auto&& [comp, ett] :
         Zip(matching_buffer.GetComponents(), matching_buffer.GetEntities())) {
      auto&& [window, ett_stor] = comp;
      glfwWindowHint(GLFW_SAMPLES, window.sample);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      auto win = glfwCreateWindow(window.size.width, window.size.height,
                                  window.title.c_str(),
                                  GetMonitorArgument(window), nullptr);
      ett_stor.ett = &ett.get();
      ett_stor.ett_mgr = &System::GetEntityManager();
      glfwSetWindowUserPointer(win, &ett_stor);
      glfwMakeContextCurrent(win);
      window.window = win;
      if (!win) {
        throw std::runtime_error("failed to create window " + window.title);
      }
    }
  }

 private:
  static GLFWmonitor* GetMonitorArgument(const comp::Window& window) {
    int count;
    auto monitors = glfwGetMonitors(&count);
    auto monitor = monitors[window.monitor_index];
    switch (window.mode) {
      case comp::Window::Mode::kWindowedFullScreen: {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
      }
      case comp::Window::Mode::kFullScreen:
        return monitor;
      case comp::Window::Mode::kWindowed:
        return nullptr;
      default:
        break;
    }
    return nullptr;
  }
};

}  // namespace system
}  // namespace ecs