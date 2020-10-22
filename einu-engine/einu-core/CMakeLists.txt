add_library(
  einu-core
  "include/einu-core/einu_engine.h"
  "include/einu-core/xnent_list.h"
  "include/einu-core/xnent.h"
  "include/einu-core/entity_view.h"
  "include/einu-core/i_xnent_pool.h"
  "include/einu-core/need_list.h"
  "include/einu-core/pool_policy.h" 
  "include/einu-core/i_entity_manager.h" 
  "include/einu-core/i_eid_pool.h" 
  "include/einu-core/eid.h"
  
  "include/einu-core/internal/entity_manager.h" 
  "include/einu-core/internal/xnent_mask.h"
  "include/einu-core/internal/xnent_pool.h"
  "include/einu-core/internal/xnent_type_id_register.h" 
   
  "src/dummy.cpp"
  
  
  "include/einu-core/internal/eid_pool.h")

target_include_directories(einu-core PUBLIC "include")
target_link_libraries(einu-core 
  PUBLIC einu-rtti einu-tmp einu-util
  PUBLIC absl::flat_hash_map
)
