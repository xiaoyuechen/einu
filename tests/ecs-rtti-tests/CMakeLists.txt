add_executable(ecs-rtti-tests "class_index_test.cpp" "class_index_storage_test.cpp" "class_index_register_test.cpp")

target_link_libraries(ecs-rtti-tests PRIVATE ecs-rtti gtest gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(ecs-rtti-tests)