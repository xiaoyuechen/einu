

#include <random>

#include "ecs-engine/core/component_context.h"
#include "ecs-engine/core/entity_manager.h"
#include "ecs-engine/extension/component/entity_storage.h"
#include "ecs-engine/extension/component/instanced_sprite_component.h"
#include "ecs-engine/extension/component/singleton_camera_component.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/extension/policy/threading_model.h"
#include "ecs-engine/extension/system/create_glfw_window.h"
#include "ecs-engine/extension/system/glfw_input.h"
#include "ecs-engine/extension/system/initialize_glad.h"
#include "ecs-engine/extension/system/initialize_glfw.h"
#include "ecs-engine/extension/system/instanced_sprite_rendering_system.h"
#include "ecs-engine/graphics/graphics.h"
#include "ecs-engine/window/gl_window.h"

namespace ecs {

struct ISRTest : testing::Test {
  using MyEntityManager = EntityManager<>;
  using MyEntity = Entity<MyEntityManager>;
  using MyEntityPool = EntityPool<MyEntity>;
  using MyComponentList =
      ComponentList<comp::Window, TransformComponent, InstancedSpriteComponent,
                    comp::Input, comp::EntityStorage<MyEntityManager>>;
  using MySingletonComponentList =
      SingletonComponentList<SingletonCameraComponent>;
  using MyComponentContext =
      ComponentContext<MyComponentList, MySingletonComponentList>;

  ISRTest()
      : entity_pool(1000)
      , ett_mgr(entity_pool, component_pool_manager,
                singleton_component_manager)
      , create_window(ett_mgr)
      , glfw_input(ett_mgr) {
    component_pool_manager.Make<TransformComponent>(1000);
    component_pool_manager.Make<InstancedSpriteComponent>(1000);
    component_pool_manager.Make<comp::Window>(10);
    component_pool_manager.Make<comp::Input>(10);
    component_pool_manager.Make<comp::EntityStorage<MyEntityManager>>(10);
    {
      auto& ett = ett_mgr.CreateEntity();
      auto& win = ett.AddComponent<comp::Window>();
      win.size = comp::Window::Size{640, 320};
      win.title = "input";
      input_comp = &ett.AddComponent<comp::Input>();
      ett.AddComponent<comp::EntityStorage<MyEntityManager>>();
    }
    {
      auto& ett = ett_mgr.CreateEntity();
      auto& win = ett.AddComponent<comp::Window>();
      win.size = comp::Window::Size{1080, 720};
      ett.AddComponent<comp::EntityStorage<MyEntityManager>>();
    }
    singleton_component_manager.Make<SingletonCameraComponent>();
  }

  MyComponentContext context;
  MyEntityPool entity_pool;
  ComponentPoolManager component_pool_manager;
  SingletonComponentManager singleton_component_manager;
  MyEntityManager ett_mgr;
  system::CreateGlfwWindow<MyEntityManager> create_window;
  system::IntializeGlfw initialize_glfw;
  system::InitializeGlad initialize_glad;
  system::GlfwInput<MyEntityManager> glfw_input;
  ecs::comp::Input* input_comp = nullptr;
};

TEST_F(ISRTest, Render) {
  initialize_glfw.Init();
  create_window.Create();

  initialize_glad.Init();
  glfw_input.SetCallbacks();

  auto tex = Texture{};
  tex.LoadFromFile("ecs-engine-test/resource/white-triangle.png");
  auto vertex_shader = VertexShader{};
  vertex_shader.LoadFromFile(
      "ecs-engine/resource/shader/instanced_sprite_vertex_shader.glsl");
  auto fragment_shader = FragmentShader{};
  fragment_shader.LoadFromFile(
      "ecs-engine/resource/shader/instanced_sprite_fragment_shader.glsl");
  auto instanced_sprite_shader = ShaderProgram(vertex_shader, fragment_shader);
  InstancedSpriteRenderingSystem<MyEntityManager> sys(ett_mgr,
                                                      instanced_sprite_shader);

  Sampler sampler{};
  sampler.Set(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  sampler.Bind();
  Sprite sprite{tex, {0, 0, tex.Width(), tex.Height()}};
  auto& cam =
      ett_mgr.GetSingletonComponentManager().Get<SingletonCameraComponent>();
  cam.projection =
      ecs::Projection{ecs::Projection::Type::ORTHOGRAPHIC,
                      ecs::Projection::OrthographicAttrib{0, 1920, 0, 1080}};

  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution_x(0, 1920);
  std::uniform_int_distribution<int> distribution_y(0, 1080);
  std::uniform_real_distribution<float> distribution_rotate(0, 360);

  for (auto i = std::size_t(0); i != 50; ++i) {
    auto& ett = ett_mgr.CreateEntity();
    auto& transform_comp = ett.AddComponent<TransformComponent>();
    auto& transform = transform_comp.transform;
    transform.SetPosition(
        glm::vec3(distribution_x(generator), distribution_y(generator), 0));
    transform.SetRotation(glm::quat(
        glm::vec3(0, 0, glm::radians(distribution_rotate(generator)))));
    transform.SetScale(glm::vec3(0.05f, 0.1f, 1.f));
    auto& inst_sprite = ett.AddComponent<InstancedSpriteComponent>();
    inst_sprite.sprite = &sprite;
  }

  ComponentEntityBuffer<ecs::comp::Window> buffer;
  ett_mgr.GetMatchingComponentsEntities<ecs::comp::Window>(buffer);
  auto&& [win] = buffer.GetComponents()[1];

  while (true) {
    sys.Render();
    glfwPollEvents();
    glfwSwapBuffers(static_cast<GLFWwindow*>(win.window));

    if (input_comp->GetKeyboardKey(KeyboardKey::kQ)) {
      break;
    }
  }
}

}  // namespace ecs