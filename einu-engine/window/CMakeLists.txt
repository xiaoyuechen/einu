add_library(
  window
  "include/einu-engine/window/input.h"
  "include/einu-engine/window/comp_window.h"
  "include/einu-engine/window/sys_window.h"
  "include/einu-engine/window/internal/glfw_input_def.h"
  "include/einu-engine/window/gl_proc.h"
  "src/sys_window.cpp"
  "src/gl_proc.cc")

add_library(einu::window ALIAS window)

set_target_properties(window PROPERTIES FOLDER "einu-engine")

target_include_directories(
  window
  PUBLIC "include"
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  window
  PUBLIC einu::core glm
  PRIVATE glfw)
