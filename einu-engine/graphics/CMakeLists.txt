add_library(
  graphics
  "include/einu-engine/graphics.h"
  "include/einu-engine/graphics/components.h"
  "include/einu-engine/graphics/singlenents.h"
  "include/einu-engine/graphics/sys_render.h"
  "include/einu-engine/graphics/gl_error.h"
  "include/einu-engine/graphics/sys_resource.h"
  "include/einu-engine/graphics/resource_type.h"
  "src/sys_render.cc"
  "src/sys_resource_shader.cc"
  "src/sys_resource_vertex_array.cc"
  "src/sys_resource_vertex_buffer.cc"
  "shaders/instanced_sprite_fragment_shader.glsl"
  "shaders/instanced_sprite_vertex_shader.glsl")

add_library(einu::graphics ALIAS graphics)

set_target_properties(graphics PROPERTIES FOLDER "einu-engine")

target_include_directories(
  graphics
  PUBLIC "include"
  PRIVATE "src")

target_link_libraries(
  graphics
  PUBLIC einu::core einu::window absl::flat_hash_map
  PRIVATE glad)
