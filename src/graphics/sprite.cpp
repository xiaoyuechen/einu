#include "einu-engine/graphics/sprite.h"

namespace einu {

Sprite::Sprite(const Texture& tex)
    : Sprite(tex, IntRect{0, 0, tex.Width(), tex.Height()}) {}

Sprite::Sprite(const Texture& tex, const IntRect& rect)
    : texture(tex)
    , texture_rect(rect) {}

void Sprite::UpdateTextureRect() noexcept {
  texture_rect = IntRect{0, 0, texture.Width(), texture.Height()};
}

void Sprite::CenterOrigin() noexcept {
  transform = glm::translate(
      glm::vec3(-texture_rect.width / 2.f, -texture_rect.height / 2.f, 0.f));
}

}  // namespace einu
