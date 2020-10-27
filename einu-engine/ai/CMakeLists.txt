add_library(ai "include/einu-engine/ai/behavior_tree.h" "src/behavior_tree.cc")

add_library(einu::ai ALIAS ai)

target_include_directories(
  ai
  PUBLIC "include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ai PUBLIC einu::core einu::common absl::flat_hash_map)
