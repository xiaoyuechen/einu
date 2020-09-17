set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/ecs-engine)

set(HEADERS
  ${HEADER_DIR}/core/ecs_engine.h
)

add_library(ecs-engine INTERFACE)

target_include_directories(ecs-engine INTERFACE 
  ${PROJECT_SOURCE_DIR}/include)

target_sources(ecs-engine INTERFACE
  ${HEADERS}  
)

#target_link_libraries(ecs-engine PRIVATE glfw)
target_link_libraries(ecs-engine INTERFACE glm)

source_group(
  TREE ${PROJECT_SOURCE_DIR}/include/ecs-engine
  PREFIX "Header Files"
  FILES ${HEADERS}
)