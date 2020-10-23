option(core_build_tests OFF)

add_library(core INTERFACE)
add_library(einu::core ALIAS core)

target_include_directories(core INTERFACE "include")

target_link_libraries(
  core 
  INTERFACE 
    absl::flat_hash_map
)

if(core_build_tests)
  add_subdirectory(tests)
endif()
