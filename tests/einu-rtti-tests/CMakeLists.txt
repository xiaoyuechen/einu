add_executable(einu-rtti-tests 
  "class_index_test.cpp" 
  "class_index_storage_test.cpp" 
  "class_index_register_test.cpp" 
)

target_link_libraries(einu-rtti-tests 
  PRIVATE einu-rtti 
  PRIVATE gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(einu-rtti-tests)