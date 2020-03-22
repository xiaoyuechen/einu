#pragma once

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/math/transform.h"

namespace ecs {

struct TransformComponent : public ComponentTag {
  using Transform = Transform<transform_policy::NoCache>;
  Transform transform{};
};

}  // namespace ecs