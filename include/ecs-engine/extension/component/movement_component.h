#pragma once

#include <algorithm>

#include "einu-engine/core/i_component.h"
#include "einu-engine/math/glm.h"

namespace einu {

struct MovementComponent : public IComponent {
  glm::vec3 direction{};
  float speed = 0;
  float max_speed = 0;
};

namespace movement_component_util {

glm::vec3 GetVelocity(const MovementComponent& movement_comp);

}

//////////////////////////////////////////////////////////////////////////

namespace movement_component_util {

inline glm::vec3 GetVelocity(const MovementComponent& movement_comp) {
  auto speed = std::min(movement_comp.speed, movement_comp.max_speed);
  return movement_comp.direction * speed;
}

}  // namespace movement_component_util

}  // namespace einu