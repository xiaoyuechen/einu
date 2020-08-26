#pragma once

#include <glad/glad.h>

#include "ecs-engine/graphics/color.h"

namespace ecs {
namespace window {

class Clearer {
 public:
  enum class Mode {
    kNone = 0,
    kColorBuffer = GL_COLOR_BUFFER_BIT,
    kDepthBuffer = GL_DEPTH_BUFFER_BIT,
    kStencilBuffer = GL_STENCIL_BUFFER_BIT,
  };

  struct Setting {
    using Color = Color<>;
    Mode mode = Mode::kNone;
    Color color{};
  };

  Clearer(const Setting& setting)
      : setting_(setting) {}

  auto GetSetting() const { return setting_; }
  auto& GetSetting() { return setting_; }

  void GLClear() const;

 private:
  Setting setting_{};
};

}  // namespace window
}  // namespace ecs