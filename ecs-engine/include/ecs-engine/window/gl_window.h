#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ecs-engine/window/gl_clearer.h"
#include "ecs-engine/window/gl_closer.h"
#include "ecs-engine/window/gl_context.h"
#include "ecs-engine/window/gl_creater.h"
#include "ecs-engine/window/gl_timer.h"
#include "ecs-engine/window/gl_input_callback_storage.h"

namespace ecs {
namespace window {

class GLWindow {
 public:
  GLWindow(GLContext& context);

 private:
  GLContext& context_;
  GLCreater& creater_;
  GLInputCallbackStorage input_callbacks_;
};

}  // namespace window
}  // namespace ecs
