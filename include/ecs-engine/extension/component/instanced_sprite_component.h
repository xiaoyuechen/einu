#pragma once

#include <array>

#include "einu-engine/core/i_component.h"
#include "einu-engine/extension/component/transform_component.h"
#include "einu-engine/graphics/color.h"
#include "einu-engine/graphics/graphics.h"

namespace einu {

struct InstancedSpriteComponent : public IComponent {
  using Color = Color<>;
  const Sprite* sprite = nullptr;
  Color color{0xff, 0xff, 0xff, 0xff};
};

}  // namespace einu