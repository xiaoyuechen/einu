#ifndef GL_CONTEXT_H_
#define GL_CONTEXT_H_

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

#endif  // GL_CONTEXT_H_
