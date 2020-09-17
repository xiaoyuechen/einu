include(GoogleTest)

add_executable(tests color_test.cpp)

target_link_libraries(tests PRIVATE ecs-engine gtest gmock gtest_main)

gtest_discover_tests(tests)