#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/graphics/sys_render.h>
#include <einu-engine/graphics/sys_resource.h>
#include <einu-engine/window/sys_window.h>

#include <iostream>

int main() {
  using namespace einu;

  using ComponentList = XnentList<window::comp::Window>;
  using SinglenentList = XnentList<graphics::sgln::ResourceTable>;
  using NeedList = NeedList<ComponentList, SinglenentList>;
  using EnginePolicy = EnginePolicy<NeedList>;
  using Engine = EinuEngine<EnginePolicy>;

  Engine engine;

  auto eid_pool = engine.CreateEIDPool();
  auto comp_pool = engine.CreateComponentPool();
  auto sgln_pool = engine.CreateSinglenentPool();
  auto ett_mgr = engine.CreateEntityManager();
  ett_mgr->SetEIDPool(*eid_pool);
  ett_mgr->SetComponentPool(*comp_pool);
  ett_mgr->SetSinglenentPool(*sgln_pool);

  auto eid = ett_mgr->CreateEntity();
  auto& win_comp = ett_mgr->AddComponent<window::comp::Window>(eid);

  auto& resource_table =
      ett_mgr->AddSinglenent<graphics::sgln::ResourceTable>();

  window::sys::Init();

  window::sys::Create(win_comp);
  window::sys::MakeContextCurrent(win_comp);

  graphics::sys::LoadGL();

  graphics::sys::Create<graphics::ResourceType::VertexArray>(resource_table,
                                                             "vao");

  graphics::sys::Create<graphics::ResourceType::VertexShader>(
      resource_table, "vshader", "shaders/instanced_sprite_vertex_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::FragmentShader>(
      resource_table, "fshader",
      "shaders/instanced_sprite_fragment_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::ShaderProgram>(
      resource_table, "program", "vshader", "fshader");

  while (!win_comp.shouldClose) {
    window::sys::PoolEvents(win_comp);
    window::sys::SwapBuffer(win_comp);
  }

  graphics::sys::Destroy<graphics::ResourceType::ShaderProgram>(resource_table,
                                                                "program");
  graphics::sys::Destroy<graphics::ResourceType::FragmentShader>(resource_table,
                                                                 "fshader");
  graphics::sys::Destroy<graphics::ResourceType::VertexShader>(resource_table,
                                                               "vshader");
  graphics::sys::Destroy<graphics::ResourceType::VertexArray>(resource_table,
                                                              "vao");

  return 0;
}
