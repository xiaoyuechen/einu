#pragma once

#include "einu-engine/math/primitive.h"
#include "einu-engine/graphics/texture.h"
#include "einu-engine/math/glm.h"

namespace einu {

struct Sprite {
  Sprite(const Texture& tex);
  Sprite(const Texture& tex, const IntRect& rect);

  void UpdateTextureRect() noexcept;
  void CenterOrigin() noexcept;

  const Texture& texture;
  IntRect texture_rect{};
  glm::mat4 transform = glm::mat4{1.0f};
};

}  // namespace einu

