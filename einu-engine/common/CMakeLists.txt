add_library(
  common
  "include/einu-engine/common/sys_movement.h"
  "include/einu-engine/common/cmp_movement.h"
  "include/einu-engine/common/primitives.h"
  "include/einu-engine/common/cmp_transform.h"
  "include/einu-engine/common/sgl_time.h"
  "src/sys_movement.cc")

add_library(einu::common ALIAS common)

set_target_properties(common PROPERTIES FOLDER "einu-engine")

target_include_directories(common PUBLIC "include")
target_link_libraries(common PUBLIC glm einu::core)
