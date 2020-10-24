add_library(glad "include/glad/glad.h" "include/KHR/khrplatform.h" "src/glad.c")

set_source_files_properties("src/glad.c" PROPERTIES LANGUAGE CXX)

target_include_directories(glad PUBLIC "include/")
