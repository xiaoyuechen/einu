#include "ecs-core/entity_manager.h"

namespace ecs {

struct C_0 : IComponent {};
struct C_1 : IComponent {};
struct C_2 : IComponent {};
struct C_3 : IComponent {};
struct C_4 : IComponent {};
struct C_5 : IComponent {};
struct C_6 : IComponent {};

using MyComponentList = ComponentList<C_0, C_1, C_3, C_4>;
using MyComponentSetting = ComponentSetting<MyComponentList>;

class MyComponentManagerPolicy {
 public:
  MyComponentManagerPolicy()
      : c_0_manager_{std::make_unique<FixedSizePool<C_0>>(100)}
      , c_1_manager_{std::make_unique<FixedSizePool<C_1>>(666)} {}

  const auto& GetComponentManager(Type2Type<C_0>) const { return c_0_manager_; }
  auto& GetComponentManager(Type2Type<C_0>) { return c_0_manager_; }
  const auto& GetComponentManager(Type2Type<C_1>) const { return c_1_manager_; }
  auto& GetComponentManager(Type2Type<C_1>) { return c_1_manager_; }

 private:
  ComponentManager<C_0> c_0_manager_;
  ComponentManager<C_1> c_1_manager_;
};

}  // namespace ecs

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  using namespace ecs;
  EntityManager<MyComponentSetting, MyComponentManagerPolicy> ett_mgr;

  ett_mgr.SpawnEntity(); 

  return 0;
}