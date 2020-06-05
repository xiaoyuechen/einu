#pragma once

#include "ecs-engine/core/i_singleton_component.h"
#include "ecs-engine/graphics/projection.h"
#include "ecs-engine/graphics/view.h"

namespace ecs {
struct SingletonCameraComponent : public ISingletonComponent {
  Projection projection;
  View view;
};
}  // namespace ecs
