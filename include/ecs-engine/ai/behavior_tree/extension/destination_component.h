#pragma once

#include "einu-engine/core/i_component.h"
#include "einu-engine/math/glm.h"

namespace einu {
namespace ai {
namespace bt {

struct DestinationComponent : public Xnent {
  glm::vec3 destination{};
  float tolerance_radius = 1.f;
};

}  // namespace bt
}  // namespace ai
}  // namespace einu