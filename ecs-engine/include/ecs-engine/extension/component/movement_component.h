#pragma once

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

struct MovementComponent : public ecs::ComponentTag {
  glm::vec3 direction;
  float max_speed;
};

namespace movement_component_util {

glm::vec3 GetVelocity(const MovementComponent& movement_comp);

}

//////////////////////////////////////////////////////////////////////////

namespace movement_component_util {

inline glm::vec3 GetVelocity(const MovementComponent& movement_comp) {
  return movement_comp.direction * movement_comp.max_speed;
}

}  // namespace movement_component_util

}  // namespace ecs