add_library(
  einu-window
  "input.h"
  "comp_window.h"
  "sys_window.h"
  "sys_window.cpp"
  "internal/glfw_input_def.h"
  "gl_proc.h"
  "gl_proc.cc"
)

target_link_libraries(
  einu-window
  PUBLIC einu-core einu-util glm 
  PRIVATE glfw
)

target_include_directories(
  einu-window
  PUBLIC "${PROJECT_SOURCE_DIR}/einu-engine/"
)