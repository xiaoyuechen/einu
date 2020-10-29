add_executable(
  astar
  "src/main.cc"
  "src/app.h"
  "src/app.cc"
  "src/cell.h"
  "src/sgl_world_state.h"
  "src/engine_policy.h"
  "src/sys_movement.h"
  "src/sys_rotate.h"
  "src/sys_rotate.cc"
  "src/sys_cell.h"
  "src/sys_cell.cc"
  "src/cmp.h"
  "src/sys_find_path.h"
  "src/sys_starchaser.h"
  "src/sys_starchaser.cc"
  "src/sys_find_path.cc"
  "src/sys_create_entity.cc"
  "src/sys_create_entity.h")

set_target_properties(astar PROPERTIES FOLDER "einu-engine/examples")

target_include_directories(astar PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(astar PUBLIC einu::core einu::common einu::ai
                                   einu::window einu::graphics)

get_target_property(graphics_source_dir einu::graphics SOURCE_DIR)

add_custom_command(
  TARGET astar
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${graphics_source_dir}/shaders
          ${CMAKE_CURRENT_BINARY_DIR}/shaders
  COMMENT "Copying shaders")

add_custom_command(
  TARGET astar
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
  COMMENT "Copying assets")
