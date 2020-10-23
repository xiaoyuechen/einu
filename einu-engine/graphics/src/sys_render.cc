#include "einu-engine/graphics/sys_render.h"

#include <glad/glad.h>

#include "einu-engine/graphics/gl_error.h"

namespace einu {
namespace graphics {
namespace sys {

void LoadGL() {
  if (!gladLoadGLLoader(
          reinterpret_cast<GLADloadproc>(window::GetProcAddress))) {
    throw GLError{"Failed to load OpenGL"};
  }
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu