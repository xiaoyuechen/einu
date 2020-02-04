#include "ecs-engine/window/gl_context.h"

#include "ecs-engine/graphics/gl_error.h"

namespace ecs {

namespace {
void InitializeGLFW() {
  if (!glfwInit()) {
    throw GLError("could not initialize glfw");
  }
  glfwSetErrorCallback(GLErrorCallback);
}

void InitializeGLAD() {
  auto proc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
  if (!gladLoadGLLoader(proc)) {
    throw GLError("could not initialize glad");
  }
}
}  // namespace

GLContext::GLContext() {
  InitializeGLFW();
}

GLContext::~GLContext() { glfwTerminate(); }

}  // namespace ecs