#include "ecs-engine/input/input.h"

namespace ecs {
namespace input {

const char* GetKeyName(KeyboardKey key) {
  auto id = static_cast<int>(key);
  auto scancode = glfwGetKeyScancode(id);
  return glfwGetKeyName(id, scancode);
}

}  // namespace input
}  // namespace ecs