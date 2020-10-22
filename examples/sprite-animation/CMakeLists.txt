add_executable(
  sprite-animation
  "main.cpp"
)

target_link_libraries(
  sprite-animation
  PRIVATE einu-core einu-window einu-graphics
)