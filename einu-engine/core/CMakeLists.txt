option(EINU_CORE_BUILD_TESTS OFF)
option(EINU_CORE_PROFILE OFF)

add_library(core INTERFACE)
add_library(einu::core ALIAS core)

target_include_directories(core INTERFACE "include")

target_link_libraries(core INTERFACE absl::flat_hash_map bitplusplus)

if(EINU_CORE_PROFILE)
  target_link_libraries(core INTERFACE easy_profiler)
  target_compile_definitions(core INTERFACE "EINU_CORE_PROFILE")
endif()

if(EINU_CORE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
