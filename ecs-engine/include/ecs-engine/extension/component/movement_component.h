#ifndef MOVEMENT_COMPONENT_H_
#define MOVEMENT_COMPONENT_H_

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {
struct MovementComponent : public ecs::ComponentTag {
  glm::vec3 velocity;
};
}  // namespace ecs

#endif  // MOVEMENT_COMPONENT_H_
