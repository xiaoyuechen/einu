#include "ecs-engine/window/gl_clearer.h"

namespace ecs {
namespace window {

void Clearer::GLClear() const {
  auto scaled_color = ScaleZeroOne(setting_.color, ~std::uint8_t{0});
  glClearColor(scaled_color.R(), scaled_color.G(), scaled_color.B(),
               scaled_color.A());
  glClear(static_cast<GLbitfield>(setting_.mode));
}

}  // namespace window
}  // namespace ecs