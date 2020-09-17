add_executable(ecs-core-tests test.cpp)

target_link_libraries(ecs-core-tests PRIVATE ecs-core gtest gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(ecs-core-tests)