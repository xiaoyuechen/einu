add_executable(sprite-animation "include/sprite-animation/app.h" "src/app.cc"
                                "src/main.cc")

set_target_properties(sprite-animation PROPERTIES FOLDER "einu-engine/examples")

target_include_directories(
  sprite-animation
  PUBLIC "include"
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sprite-animation PRIVATE einu::core einu::window
                                               einu::graphics)

get_target_property(graphics_source_dir einu::graphics SOURCE_DIR)

add_custom_command(
  TARGET sprite-animation
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${graphics_source_dir}/shaders"
          "$<TARGET_FILE_DIR:sprite-animation>/shaders"
  COMMENT "Copying shaders")

add_custom_command(
  TARGET sprite-animation
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:sprite-animation>/assets"
  COMMENT "Copying assets")
