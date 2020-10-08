add_executable(einu-util-tests 
  "object_pool_test.cc" 
)

target_link_libraries(einu-util-tests 
  PRIVATE einu-util 
  PRIVATE gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(einu-util-tests)