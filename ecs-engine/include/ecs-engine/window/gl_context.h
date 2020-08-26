#pragma once

#include <glad/glad.h>

// glfw needs to be included last
#include <GLFW/glfw3.h>

namespace ecs {
namespace window {

class GLContext {
 public:
  GLContext();
  ~GLContext();

  void MakeContextCurrent(void* window);
};

}  // namespace window
}  // namespace ecs
