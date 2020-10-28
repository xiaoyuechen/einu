add_library(
  ai
  "include/einu-engine/ai/behavior_tree.h"
  "include/einu-engine/ai/cmp_destination.h"
  "include/einu-engine/ai/bt_move_to.h"
  "src/behavior_tree.cc"
  "src/bt_move_to.cc")

add_library(einu::ai ALIAS ai)

set_target_properties(ai PROPERTIES FOLDER "einu-engine")

target_include_directories(
  ai
  PUBLIC "include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ai PUBLIC einu::core einu::common absl::flat_hash_map)
