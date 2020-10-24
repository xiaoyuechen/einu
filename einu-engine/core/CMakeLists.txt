option(CORE_BUILD_TESTS OFF)

add_library(core INTERFACE)
add_library(einu::core ALIAS core)

target_include_directories(core INTERFACE "include")

target_link_libraries(core INTERFACE absl::flat_hash_map)

if(CORE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
