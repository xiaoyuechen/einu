add_library(
  einu-graphics
  "sys_render.h"
  "sys_render.cc"
  "comp_camera.h")

target_include_directories(
  einu-graphics
  PUBLIC "${PROJECT_SOURCE_DIR}/einu-engine/"
)

target_link_libraries(
  einu-graphics
  PUBLIC einu-core einu-window glad
)