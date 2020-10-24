#include "einu-engine/window/gl_proc.h"

#include <GLFW/glfw3.h>

namespace einu {
namespace window {

GLLoaderProc GetProcAddress(const char* procname) {
  return glfwGetProcAddress(procname);
}

}  // namespace window
}  // namespace einu
