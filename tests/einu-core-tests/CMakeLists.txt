add_executable(
  einu-core-tests 
  "xnent_mask_test.cc" 
  "entity_view_test.cc"
  "einu_engine_test.cc"
  "need_list_test.cc"
  "entity_test.cc"
  "xnents.h"
  "component_pool_test.cc"
  "entity_pool_test.cc"
  "world_test.cc"
   "mock_entity.h")

target_link_libraries(einu-core-tests 
  PRIVATE einu-core 
  PRIVATE gtest gtest_main gmock gmock_main
)

include(GoogleTest)
gtest_discover_tests(einu-core-tests)