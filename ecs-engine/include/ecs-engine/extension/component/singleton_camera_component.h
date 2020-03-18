#pragma once

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/graphics/projection.h"
#include "ecs-engine/graphics/view.h"

namespace ecs {
struct SingletonCameraComponent : public ComponentTag {
  Projection projection;
  View view;
};
}  // namespace ecs

