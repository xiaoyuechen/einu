add_executable(
  sprite-animation
  "main.cpp"
)

set_target_properties(sprite-animation PROPERTIES FOLDER "einu-engine/examples")

target_link_libraries(
  sprite-animation
  PRIVATE einu::core einu::window einu::graphics
)

get_target_property(graphics_source_dir einu::graphics SOURCE_DIR)
add_custom_command(TARGET sprite-animation POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${graphics_source_dir}/shaders
                           ${CMAKE_CURRENT_BINARY_DIR}/shaders)
