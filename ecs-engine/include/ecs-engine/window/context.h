#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <glad/glad.h>

// glfw needs to be included last
#include <GLFW/glfw3.h>

namespace ecs {

class Context {
 public:
  Context();
  ~Context();
};

}  // namespace ecs

#endif  // CONTEXT_H_
