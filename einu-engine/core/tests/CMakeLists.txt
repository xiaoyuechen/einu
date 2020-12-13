add_executable(
  core-tests
  "src/bit_test.cc"
  "src/class_index_test.cc"
  "src/component_pool_test.cc"
  "src/einu_engine_test.cc"
  "src/entity_manager_test.cc"
  "src/entity_view_test.cc"
  "src/need_list_test.cc"
  "src/object_pool_test.cc"
  "src/xnent_mask_test.cc"
  "src/xnent_type_id_register_test.cc"
  "src/xnents.h")

set_target_properties(core-tests PROPERTIES FOLDER "einu-engine")

target_include_directories(core-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core-tests PRIVATE einu::core gtest gtest_main gmock
                                         gmock_main)

include(GoogleTest)
gtest_discover_tests(core-tests)
