add_executable(
  astar
  "src/app.cc"
  "src/app.h"
  "src/cell.h"
  "src/cmp.h"
  "src/engine_policy.h"
  "src/main.cc"
  "src/sgl_world_state.h"
  "src/sys_cell.cc"
  "src/sys_cell.h"
  "src/sys_create_entity.cc"
  "src/sys_create_entity.h"
  "src/sys_find_path.cc"
  "src/sys_find_path.h"
  "src/sys_movement.h"
  "src/sys_rotate.cc"
  "src/sys_rotate.h"
  "src/sys_starchaser.cc"
  "src/sys_starchaser.h")

set_target_properties(astar PROPERTIES FOLDER "einu-engine/examples")

target_include_directories(astar PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(astar PUBLIC einu::core einu::common einu::ai
                                   einu::window einu::graphics)

get_target_property(graphics_source_dir einu::graphics SOURCE_DIR)

add_custom_command(
  TARGET astar
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory #
    "${graphics_source_dir}/shaders" #
    "$<TARGET_FILE_DIR:astar>/shaders"
  COMMENT "Copying shaders")

add_custom_command(
  TARGET astar
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory #
    "${CMAKE_CURRENT_SOURCE_DIR}/assets" #
    "$<TARGET_FILE_DIR:astar>/assets"
  COMMENT "Copying assets")
