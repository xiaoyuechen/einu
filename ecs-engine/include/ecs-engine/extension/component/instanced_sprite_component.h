#ifndef INSTANCED_SPRITE_COMPONENT_H_
#define INSTANCED_SPRITE_COMPONENT_H_

#include <array>

#include "ecs-engine/core/component_tag.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/graphics/graphics.h"

namespace ecs {

struct InstancedSpriteComponent : public ComponentTag {
  Sprite* sprite = nullptr;
  std::array<uint8_t, 4> color{0xff, 0xff, 0xff, 0xff};
};
}  // namespace ecs

#endif  // INSTANCED_SPRITE_COMPONENT_H_