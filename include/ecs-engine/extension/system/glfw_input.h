#pragma once

#include <GLFW/glfw3.h>

#include "einu-engine/core/system.h"
#include "einu-engine/extension/component/entity_storage.h"
#define GLFW_INPUT_ENUM
#include "einu-engine/extension/component/input.h"
#include "einu-engine/extension/component/window.h"

namespace einu {
namespace system {

using GlfwInputRequiredComponentList = ComponentList<comp::Window, comp::Input>;

template <typename EntityManager>
class GlfwInput : System<EntityManager, GlfwInputRequiredComponentList> {
 public:
  using System = System<EntityManager, GlfwInputRequiredComponentList>;
  using System::System;

  void SetCallbacks() {
    System::RefreshMatchingBuffer();
    for (auto& [window, input] : System::GetMatchingBuffer().GetComponents()) {
      auto glfwWindow = static_cast<GLFWwindow*>(window.window);
      glfwSetMouseButtonCallback(glfwWindow, MouseButtonCallback);
      glfwSetKeyCallback(glfwWindow, KeyCallback);
      glfwSetCursorPosCallback(glfwWindow, CursorPosCallback);
    }
  }

  void Update() {
    System::RefreshMatchingBuffer();
    for (auto& [window, input] : System::GetMatchingBuffer().GetComponents()) {
      auto cursor_next = input.hammer + 1;
      input.hammer = cursor_next == input.kInputBufferSize ? 0 : cursor_next;

      for (auto&& buffer : input.mouse_button_buffer_map) {
        buffer[input.hammer] = false;
      }

      for (auto&& buffer : input.keyboard_key_buffer_map) {
        buffer[input.hammer] = false;
      }

      input.modifier_key_buffer[input.hammer] = static_cast<ModifierKeyFlag>(0);
    }
    glfwPollEvents();
  }

 private:
  static auto& GetInputComponent(GLFWwindow& window) {
    auto& ett_stor = *static_cast<comp::EntityStorage<EntityManager>*>(
        glfwGetWindowUserPointer(&window));
    return ett_stor.ett->GetComponent<comp::Input>();
  }

  static void MouseButtonCallback(GLFWwindow* window, int button, int action,
                                  int mods) {
    auto& input_comp = GetInputComponent(*window);
    auto&& button_state =
        input_comp.GetMouseButton(static_cast<MouseButton>(button));
    button_state = action;
    auto&& mods_state = input_comp.GetModifierKeyFlag();
    mods_state |= static_cast<ModifierKeyFlag>(mods);
  }

  static void KeyCallback(GLFWwindow* window, int key,
                          [[maybe_unused]] int scancode, int action, int mods) {
    auto& input_comp = GetInputComponent(*window);
    auto key_enum = static_cast<KeyboardKey>(key);
    auto&& key_state = input_comp.GetKeyboardKey(key_enum);
    key_state = action;
    auto&& mods_state = input_comp.GetModifierKeyFlag();
    mods_state |= static_cast<ModifierKeyFlag>(mods);
  }

  static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto& input_comp = GetInputComponent(*window);
    auto& cursor_pos = input_comp.GetCursorPos();
    cursor_pos.x = static_cast<float>(xpos);
    cursor_pos.y = static_cast<float>(ypos);
  }
};
}  // namespace system
}  // namespace einu
