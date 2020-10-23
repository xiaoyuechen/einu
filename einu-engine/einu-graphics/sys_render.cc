#include "einu-graphics/sys_render.h"

#include <glad/glad.h>

#include <stdexcept>

namespace einu {
namespace graphics {
namespace sys {

void LoadGL() {
  if (!gladLoadGLLoader(
          reinterpret_cast<GLADloadproc>(window::GetProcAddress))) {
    throw std::runtime_error("failed to load OpenGL");
  }
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu