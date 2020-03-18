#include "pch.h"
// pre-compiled header

#include <ecs-engine/extension/manager/resource_manager.h>
#include <ecs-engine/graphics/texture.h>
#include <ecs-engine/window/window.h>

namespace ecs {

using TextureManager = ResourceManager<int, Texture>;
struct ResourceManagerTest : testing::Test {
  ResourceManagerTest()
      : window(Window::Mode::WINDOWED, 1280, 720, "test") {}
  Window window;
  TextureManager manager;
};

TEST_F(ResourceManagerTest, Load) {
  auto textrue = Texture{};
  manager.Load(0, "ecs-engine-test/resource/white-triangle.png");
  const auto& texture = manager.Get(0);
  EXPECT_EQ(texture.Width(), 600);
  window.SetWindowShouldClose(true);
}

}  // namespace ecs
