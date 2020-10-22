add_library(
  einu-graphics
  "render_sys.h"
  "render_sys.cc"
)

target_include_directories(
  einu-graphics
  PUBLIC "${PROJECT_SOURCE_DIR}/einu-engine/"
)

target_link_libraries(
  einu-graphics
  PUBLIC einu-core einu-window glad
)