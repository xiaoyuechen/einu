#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/graphics/sys_render.h>
#include <einu-engine/graphics/sys_shader.h>
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

  graphics::sys::CreateShader(graphics::sys::ShaderType::Vertex, "vs-1",
                              "shaders/instanced_sprite_vertex_shader.glsl",
                              resource_table);

  while (!win_comp.shouldClose) {
    window::sys::PoolEvents(win_comp);
    window::sys::SwapBuffer(win_comp);
  }

  return 0;
}
