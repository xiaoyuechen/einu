#include "ecs-engine/graphics/sprite.h"

namespace ecs {

Sprite::Sprite(const Texture& tex)
    : Sprite(tex, IntRect{0, 0, tex.Width(), tex.Height()}) {}

Sprite::Sprite(const Texture& tex, const IntRect& rect)
    : texture(tex)
    , tex_rect(rect) {}

}  // namespace ecs
