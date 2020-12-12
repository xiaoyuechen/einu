add_library(tracy "tracy/TracyClient.cpp")

target_include_directories(tracy SYSTEM PUBLIC "tracy")

target_compile_definitions(tracy PUBLIC TRACY_ENABLE)
