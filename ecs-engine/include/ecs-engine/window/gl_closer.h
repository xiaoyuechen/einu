#pragma once

#include <GLFW/glfw3.h>

namespace ecs {
namespace window {

class GLCloser {
 public:
  GLCloser(GLFWwindow* window)
      : window_(window) {}

  void SetShouldClose(bool should_close = true);
  bool ShouldClose() const;

 private:
  GLFWwindow* window_;
};

}  // namespace window
}  // namespace ecs