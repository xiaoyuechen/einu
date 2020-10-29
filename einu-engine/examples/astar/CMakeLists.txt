add_executable(astar "src/main.cc")

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
