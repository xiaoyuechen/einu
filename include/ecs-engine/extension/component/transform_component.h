#pragma once

#include "einu-engine/core/i_component.h"
#include "einu-engine/math/transform.h"

namespace einu {

struct TransformComponent : public IComponent {
  using Transform = Transform<transform_policy::NoCache>;
  Transform transform{};
};

}  // namespace einu