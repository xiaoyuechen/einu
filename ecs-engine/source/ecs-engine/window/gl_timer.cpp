#include "ecs-engine/window/gl_timer.h"

#include <GLFW/glfw3.h>

namespace ecs {
namespace window {

double GLTimer::GetTime() const { return glfwGetTime(); }

void GLTimer::SetTime(double time) { glfwSetTime(time); }

}  // namespace window
}  // namespace ecs