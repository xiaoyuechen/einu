#pragma once

#include <array>

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/graphics/graphics.h"

namespace ecs {

struct InstancedSpriteComponent : public ComponentTag {
  using Color = std::array<uint8_t, 4>;
  const Sprite* sprite = nullptr;
  Color color{0xff, 0xff, 0xff, 0xff};
};
}  // namespace ecs