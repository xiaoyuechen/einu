#pragma once

#include "ecs-engine/core/component.h"
#include "ecs-engine/math/transform.h"

namespace ecs {

struct TransformComponent : public IComponent {
  using Transform = Transform<transform_policy::NoCache>;
  Transform transform{};
};

}  // namespace ecs