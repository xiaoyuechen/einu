add_library(einu-core INTERFACE)

target_include_directories(einu-core INTERFACE "include/")

target_link_libraries(
  einu-core INTERFACE 
  einu-rtti einu-tmp einu-util 
  absl::flat_hash_map
)
