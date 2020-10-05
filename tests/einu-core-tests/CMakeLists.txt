add_executable(einu-core-tests 
  "component_list_test.cpp" 
  "entity_view_test.cpp"
)

target_link_libraries(einu-core-tests 
  PRIVATE einu-core 
  PRIVATE gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(einu-core-tests)