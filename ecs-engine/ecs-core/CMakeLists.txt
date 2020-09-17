add_library(ecs-core include/ecs-core/ecs_engine.h  src/dummy.cpp 
include/ecs-core/h.h  )

target_include_directories(ecs-core PUBLIC include)
target_link_libraries(ecs-core INTERFACE ecs-tmp)