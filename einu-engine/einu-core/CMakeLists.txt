add_library(
  einu-core
  "include/einu-core/einu_core.h"
  "src/dummy.cc"
  "include/einu-core/internal/entity.h"
  "include/einu-core/internal/xnent_type_id.h"
  "include/einu-core/internal/xnent_mask.h"
  "include/einu-core/xnent_list.h"
  "include/einu-core/xnent.h"
  "include/einu-core/i_entity.h"
  "include/einu-core/entity_view.h"
  "include/einu-core/i_entity_pool.h"
  "include/einu-core/i_component_pool.h"
  "include/einu-core/entity_buffer.h"
  "include/einu-core/i_world.h"
  "include/einu-core/need_list.h")

target_include_directories(einu-core PUBLIC "include")
target_link_libraries(einu-core INTERFACE einu-rtti einu-tmp)
