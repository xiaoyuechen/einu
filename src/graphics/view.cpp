#include "ecs-engine/graphics/view.h"

namespace ecs {

glm::mat4 View::GetViewMatrix() const {
  return glm::lookAt(position, target, up);
}

}  // namespace ecs
