#pragma once

#include "einu-engine/core/i_singleton_component.h"
#include "einu-engine/graphics/projection.h"
#include "einu-engine/graphics/view.h"

namespace einu {
struct SingletonCameraComponent : public ISingletonComponent {
  Projection projection;
  View view;
};
}  // namespace einu
