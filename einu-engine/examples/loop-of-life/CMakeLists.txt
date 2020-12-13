add_executable(
  loop-of-life
  "src/agent.h"
  "src/app.cc"
  "src/app.h"
  "src/bt_agent.cc"
  "src/bt_agent.h"
  "src/cmp_agent.h"
  "src/cmp_health.h"
  "src/main.cc"
  "src/sgl_world_state.h"
  "src/sys_agent_create.cc"
  "src/sys_agent_create.h"
  "src/sys_movement.h"
  "src/sys_rotate.cc"
  "src/sys_rotate.h"
  "src/sys_sense.cc"
  "src/sys_sense.h"
  "src/sys_world_state.cc"
  "src/sys_world_state.h")

set_target_properties(loop-of-life PROPERTIES FOLDER "einu-engine/examples")

target_include_directories(
  loop-of-life
  PUBLIC "include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(loop-of-life PUBLIC einu::core einu::common einu::ai
                                          einu::window einu::graphics)

get_target_property(graphics_source_dir einu::graphics SOURCE_DIR)

add_custom_command(
  TARGET loop-of-life
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${graphics_source_dir}/shaders"
          "$<TARGET_FILE_DIR:loop-of-life>/shaders"
  COMMENT "Copying shaders")

add_custom_command(
  TARGET loop-of-life
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:loop-of-life>/assets"
  COMMENT "Copying assets")
