#pragma once

#include <einu-core/xnent.h>

#include <cstdint>
#include <glm/glm.hpp>

namespace einu {
namespace graphics {
namespace comp {

struct Camera : public Xnent {
  std::uint32_t id;
  glm::mat4 projection;
  glm::mat4 view;
};

}  // namespace comp
}  // namespace graphics
}  // namespace einu