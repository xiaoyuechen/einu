add_executable(einu-core-tests 
  "component_list_test.cc" 
  "entity_view_test.cc"
  "einu_engine_test.cc"
 )

target_link_libraries(einu-core-tests 
  PRIVATE einu-core 
  PRIVATE gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(einu-core-tests)