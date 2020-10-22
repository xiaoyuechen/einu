#include <einu-core/einu_engine.h>
#include <einu-core/entity_view.h>
#include <einu-window/window_sys.h>

#include <iostream>

int main() {
  using namespace einu;
  using ComponentList = XnentList<window::comp::Window>;
  using SinglenentList = XnentList<>;
  using NeedList = NeedList<ComponentList, SinglenentList>;
  using EnginePolicy = EnginePolicy<NeedList>;
  using Engine = EinuEngine<EnginePolicy>;

  Engine engine;

  auto eid_pool = engine.CreateEIDPool();
  auto comp_pool = engine.CreateComponentPool();
  auto ett_mgr = engine.CreateEntityManager();
  ett_mgr->SetEIDPool(*eid_pool);
  ett_mgr->SetComponentPool(*comp_pool);

  auto eid = ett_mgr->CreateEntity();
  auto& win_comp = ett_mgr->AddComponent<window::comp::Window>(eid);

  using WindowEntityView = EntityView<XnentList<window::comp::Window>>;
  WindowEntityView window_entity_view;
  window_entity_view.View(*ett_mgr);

  window::sys::Init();

  for (auto&& [win] : window_entity_view.Components()) {
    window::sys::Create(win);
  }

  while (!win_comp.shouldClose) {
    window::sys::PoolEvents(win_comp);
  }

  return 0;
}
