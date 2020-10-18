add_library(
  einu-core
  "include/einu-core/einu_core.h"
  "include/einu-core/internal/entity.h"
  "include/einu-core/internal/xnent_type_id.h"
  "include/einu-core/internal/xnent_mask.h"
  "include/einu-core/xnent_list.h"
  "include/einu-core/xnent.h"
  "include/einu-core/i_entity.h"
  "include/einu-core/entity_view.h"
  "include/einu-core/i_entity_pool.h"
  "include/einu-core/i_xnent_pool.h"
  "include/einu-core/entity_buffer.h"
  "include/einu-core/i_world.h"
  "include/einu-core/need_list.h"
  "include/einu-core/internal/xnent_pool.h"
  "include/einu-core/internal/entity_pool.h"
  "include/einu-core/pool_policy.h" 
  "include/einu-core/internal/world.h" 
  "include/einu-core/i_world_pool.h" 
  "include/einu-core/internal/i_pool.h" 
  "include/einu-core/internal/world_pool.h"
  "src/world.cc"
  "src/world_pool.cc"
  )

target_include_directories(einu-core PUBLIC "include")
target_link_libraries(einu-core PUBLIC einu-rtti einu-tmp einu-util)
