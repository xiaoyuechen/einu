#ifndef SPRITE_H_
#define SPRITE_H_

#include "ecs-engine/graphics/rect.h"
#include "ecs-engine/graphics/texture.h"
#include "ecs-engine/math/glm.h"

namespace ecs {

struct Sprite {
  Sprite(const Texture& tex);
  Sprite(const Texture& tex, const IntRect& rect);

  const Texture& texture;
  IntRect tex_rect{};
  glm::mat4 transform = glm::mat4{1.0f};
};

}  // namespace ecs

#endif  // SPRITE_H_