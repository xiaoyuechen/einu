add_executable(einu-rtti-tests 
  "class_index_test.cc" 
  "class_index_storage_test.cc" 
   
)

target_link_libraries(einu-rtti-tests 
  PRIVATE einu-rtti 
  PRIVATE gtest gtest_main
)

include(GoogleTest)
gtest_discover_tests(einu-rtti-tests)