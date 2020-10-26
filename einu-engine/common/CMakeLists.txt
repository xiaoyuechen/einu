add_library(common INTERFACE)
add_library(einu::common ALIAS common)

target_include_directories(common INTERFACE "include")
target_link_libraries(common INTERFACE glm)
