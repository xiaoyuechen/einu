#include "pch.h"
// pre-compiled header

#include <random>

#include "ecs-engine/core/entity_manager.h"
#include "ecs-engine/extension/policy/component_manager_policy.h"
#include "ecs-engine/extension/component/instanced_sprite_component.h"
#include "ecs-engine/extension/system/instanced_sprite_rendering_system.h"
#include "ecs-engine/extension/component/singleton_camera_component.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/graphics/graphics.h"
#include "ecs-engine/window/window.h"

namespace ecs {

struct ISRTest : testing::Test {
  using MyComponentList =
      ComponentList<TransformComponent, InstancedSpriteComponent>;
  using MyComponentSetting = ComponentSetting<MyComponentList>;
  using MySingletonComponentList = ComponentList<SingletonCameraComponent>;

  class MyComponentManagerPolicy
      : public ComponentManagerPolicy<MyComponentSetting,
                                      MySingletonComponentList,
                                      MultiThreaded> {
   public:
    MyComponentManagerPolicy()
        : transform_manager_{99}
        , IS_manager_{666}
        , ComponentManagerPolicy(
              std::forward_as_tuple(transform_manager_, IS_manager_),
              std::forward_as_tuple(s_camera_)) {}

   private:
    ComponentManager<TransformComponent> transform_manager_;
    ComponentManager<InstancedSpriteComponent> IS_manager_;
    SingletonCameraComponent s_camera_;
  };

  using MyEntityManager = EntityManager<MyComponentSetting,
                                        MyComponentManagerPolicy,
                                        MultiThreaded>;

  ISRTest()
      : window(Window::Mode::WINDOWED, 1920, 1080, "application")
      , sys(ett_mgr) {
    tex.LoadFromFile("resource/white-triangle.png");
  }

  Window window;
  MyEntityManager ett_mgr;
  InstancedSpriteRenderingSystem<MyEntityManager> sys;
  Texture tex;
};

TEST_F(ISRTest, Render) {
  auto& cam = ett_mgr.GetSingletonComponent<SingletonCameraComponent>();
  // cam.view = glm::mat4(1);
  cam.projection = glm::ortho(0.f, 1920.f, 0.f, 1080.f, 0.01f, 1000.f);
  Sampler sampler{};
  sampler.Set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  sampler.Bind();
  Sprite sprite{tex, {0, 0, tex.Width(), tex.Height()}};

  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution_x(0, 1920);
  std::uniform_int_distribution<int> distribution_y(0, 1080);
  std::uniform_real_distribution<float> distribution_rotate(0, 360);

  for (auto i = std::size_t(0); i != 50; ++i) {
    auto ett_handle = ett_mgr.CreateEntity();
    ett_handle.AddComponent<TransformComponent>();
    ett_handle.GetComponent<TransformComponent>() *=
        (glm::translate(glm::vec3(
             distribution_x(generator), distribution_y(generator), 0)) *
         glm::rotate(glm::radians(distribution_rotate(generator)),
                     glm::vec3(0, 0, 1)) *
         glm::scale(glm::vec3(0.05f, 0.1f, 1.f)));
    ett_handle.AddComponent<InstancedSpriteComponent>();
    ett_handle.GetComponent<InstancedSpriteComponent>().sprite = &sprite;
  }

  while (!window.ShouldClose()) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sys.Render();

    window.SwapBuffer();
    window.PollEvents();
  }
}

}  // namespace ecs