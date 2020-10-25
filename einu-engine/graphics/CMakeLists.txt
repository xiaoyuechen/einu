add_library(
  graphics
  "include/einu-engine/graphics/components.h"
  "include/einu-engine/graphics/singlenents.h"
  "include/einu-engine/graphics/sys_render.h"
  "include/einu-engine/graphics/graphics_error.h"
  "include/einu-engine/graphics/sys_resource.h"
  "include/einu-engine/graphics/resource_type.h"
  "include/einu-engine/graphics/projection.h"
  "include/einu-engine/graphics/color.h"
  "src/sys_render.cc"
  "src/sys_resource_shader.cc"
  "src/sys_resource_vertex_array.cc"
  "src/sys_resource_vertex_buffer.cc"
  "src/sys_resource_texture.cc"
  "shaders/instanced_sprite_fragment_shader.glsl"
  "shaders/instanced_sprite_vertex_shader.glsl"
  "src/sys_resource_helper.h")

add_library(einu::graphics ALIAS graphics)

set_target_properties(graphics PROPERTIES FOLDER "einu-engine")

target_include_directories(
  graphics
  PUBLIC "include"
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  graphics
  PUBLIC einu::core einu::window absl::flat_hash_map
  PRIVATE glad stb)
