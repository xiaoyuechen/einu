add_library(
  einu-core
  "include/einu-core/einu_core.h"
  "src/dummy.cpp"
  "include/einu-core/internal/entity.h"
  "include/einu-core/internal/component_index.h"
  "include/einu-core/internal/component_index_list.h"
  "include/einu-core/component_list.h"
  "include/einu-core/i_component.h"
  "include/einu-core/i_entity.h"
  "include/einu-core/entity_view.h"
  "include/einu-core/i_entity_pool.h"
  "include/einu-core/i_component_pool.h"
  "include/einu-core/entity_buffer.h"
  "include/einu-core/i_world.h"
   )

target_include_directories(einu-core PUBLIC "include")
target_link_libraries(einu-core INTERFACE einu-rtti einu-tmp)
