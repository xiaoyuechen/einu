#pragma once

#include <glad/glad.h>

// glfw needs to be included last
#include <GLFW/glfw3.h>

namespace ecs {

class GLContext {
 public:
  GLContext();
  ~GLContext();
};

}  // namespace ecs

