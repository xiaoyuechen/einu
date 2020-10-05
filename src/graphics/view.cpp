#include "einu-engine/graphics/view.h"

namespace einu {

glm::mat4 View::GetViewMatrix() const {
  return glm::lookAt(position, target, up);
}

}  // namespace einu
