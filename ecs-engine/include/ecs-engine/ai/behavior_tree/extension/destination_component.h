#pragma once

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/glm.h"

namespace ecs {
namespace ai {
namespace bt {

struct DestinationComponent : public ComponentTag {
  glm::vec3 destination;
  float tolerance_radius;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs