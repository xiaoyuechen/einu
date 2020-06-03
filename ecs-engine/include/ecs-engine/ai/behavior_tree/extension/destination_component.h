#pragma once

#include "ecs-engine/core/component.h"
#include "ecs-engine/math/glm.h"

namespace ecs {
namespace ai {
namespace bt {

struct DestinationComponent : public IComponent {
  glm::vec3 destination{};
  float tolerance_radius = 1.f;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs