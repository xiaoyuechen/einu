add_library(
  einu-graphics
  "components.h" 
  "singlenents.h" 
  "sys_render.h"
  "sys_render.cc"
  "sys_shader.h"
  "sys_shader.cc"
  "gl_error.h"
  "shaders/instanced_sprite_fragment_shader.glsl"
  "shaders/instanced_sprite_vertex_shader.glsl" 
)

target_include_directories(
  einu-graphics
  PUBLIC "${einu_SOURCE_DIR}/einu-engine/"
)

target_link_libraries(
  einu-graphics
  PUBLIC einu-core einu-window glad absl::flat_hash_map
)
