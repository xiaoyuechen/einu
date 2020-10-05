add_library(einu-core 
  "include/einu-core/einu_core.h"
  "src/dummy.cpp" 
)

target_include_directories(einu-core PUBLIC "include")
target_link_libraries(einu-core INTERFACE einu-rtti einu-tmp)