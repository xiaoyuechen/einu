add_library(
  einu-window
  "input.h"
  "window_comp.h"
  "window_sys.h"
  "window_sys.cpp"
 
 "internal/glfw_input_def.h")

target_link_libraries(
  einu-window
  PUBLIC einu-core einu-util glm glfw
)

target_include_directories(
  einu-window
  PUBLIC "${PROJECT_SOURCE_DIR}/einu-engine/"
)