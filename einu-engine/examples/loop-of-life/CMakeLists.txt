add_executable(
  loop-of-life
  "src/main.cc"
  "src/app.h"
  "src/app.cc"
  "src/cmp_agent.h"
  "src/agent.h"
  "src/cmp_health.h"
  "src/sgl_world_state.h"
  "src/sys_world_state.cc"
  "src/sys_world_state.h"
  "src/bt_agent.h"
  "src/sys_sense.h"
  "src/sys_sense.cc"
  "src/sys_agent_create.h"
  "src/sys_agent_create.cc"
  "src/bt_agent.cc")

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
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${graphics_source_dir}/shaders
          ${CMAKE_CURRENT_BINARY_DIR}/shaders
  COMMENT "Copying shaders")

add_custom_command(
  TARGET loop-of-life
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
  COMMENT "Copying assets")
