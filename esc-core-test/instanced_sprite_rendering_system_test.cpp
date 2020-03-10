#include "pch.h"
// pre-compiled header

#include <random>

#include "ecs-engine/core/entity_manager.h"
#include "ecs-engine/extension/component/instanced_sprite_component.h"
#include "ecs-engine/extension/component/singleton_camera_component.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/extension/policy/component_manager_policy.h"
#include "ecs-engine/extension/policy/threading_model.h"
#include "ecs-engine/extension/system/instanced_sprite_rendering_system.h"
#include "ecs-engine/graphics/graphics.h"
#include "ecs-engine/window/window.h"

namespace ecs {

struct ISRTest : testing::Test {
  using MyComponentList =
      ComponentList<TransformComponent, InstancedSpriteComponent>;
  using MySingletonComponentList = ComponentList<SingletonCameraComponent>;
  using MyComponentSetting =
      ComponentSetting<MyComponentList, MySingletonComponentList>;

  class MyComponentManagerPolicy
      : public ComponentManagerPolicy<MyComponentSetting, MultiThreaded> {
   public:
    MyComponentManagerPolicy() {
      ComponentManagerPolicy::SetComponentManager(
          std::make_unique<ComponentManager<TransformComponent>>(10000));
      ComponentManagerPolicy::SetComponentManager(
          std::make_unique<ComponentManager<InstancedSpriteComponent>>(10000));
      ComponentManagerPolicy::SetSingletonComponent(
          std::make_unique<SingletonCameraComponent>());
    }
  };

  using MyEntityManager =
      EntityManager<MyComponentSetting, MyComponentManagerPolicy,
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
  Sampler sampler{};
  sampler.Set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  sampler.Bind();
  Sprite sprite{tex, {0, 0, tex.Width(), tex.Height()}};
  auto& cam = ett_mgr.GetSingletonComponent<SingletonCameraComponent>();
  cam.projection =
      ecs::Projection{ecs::Projection::Type::ORTHOGRAPHIC,
                      ecs::Projection::OrthographicAttrib{0, 1920, 0, 1080}};

  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution_x(0, 1920);
  std::uniform_int_distribution<int> distribution_y(0, 1080);
  std::uniform_real_distribution<float> distribution_rotate(0, 360);

  for (auto i = std::size_t(0); i != 50; ++i) {
    auto ett_handle = ett_mgr.CreateEntity();
    auto& transform = ett_handle.AddComponent<TransformComponent>();
    transform.SetPosition(
        glm::vec3(distribution_x(generator), distribution_y(generator), 0));
    transform.SetRotation(glm::quat(
        glm::vec3(0, 0, glm::radians(distribution_rotate(generator)))));
    transform.SetScale(glm::vec3(0.05f, 0.1f, 1.f));
    auto& inst_sprite = ett_handle.AddComponent<InstancedSpriteComponent>();
    inst_sprite.sprite = &sprite;
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