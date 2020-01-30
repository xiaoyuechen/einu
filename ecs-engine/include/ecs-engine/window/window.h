#ifndef WINDOW_H_
#define WINDOW_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ecs-engine/window/context.h"
#include "ecs-engine/window/input.h"

namespace ecs {

class Window {
 public:
  enum class Mode {
    WINDOWED,
    FULLSCREEN,
  };

  Window(Mode mode, int width, int height, const char* title);
  ~Window();

  void SetKeyCallback(const input::KeyCallback& key_callback);

 private:
  Context context_;
  GLFWwindow& window_;
};

}  // namespace ecs

#endif  // WINDOW_H_
