add_executable(
  core-tests
  "class_index_test.cc"
  "object_pool_test.cc"
  "xnent_mask_test.cc"
  "einu_engine_test.cc"
  "need_list_test.cc"
  "xnents.h"
  "component_pool_test.cc"
  "xnent_type_id_register_test.cc"
  "entity_manager_test.cc"
  "entity_view_test.cc")

set_target_properties(core-tests PROPERTIES FOLDER "einu-engine")

target_link_libraries(core-tests PRIVATE einu::core gtest gtest_main gmock
                                         gmock_main)

include(GoogleTest)
gtest_discover_tests(core-tests)
