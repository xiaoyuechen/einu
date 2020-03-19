#pragma once

#include "ecs-engine/math/primitive.h"
#include "ecs-engine/graphics/texture.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

struct Sprite {
  Sprite(const Texture& tex);
  Sprite(const Texture& tex, const IntRect& rect);

  void UpdateTextureRect() noexcept;
  void CenterOrigin() noexcept;

  const Texture& texture;
  IntRect texture_rect{};
  glm::mat4 transform = glm::mat4{1.0f};
};

}  // namespace ecs

