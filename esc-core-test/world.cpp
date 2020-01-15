#include "pch.h"
#include "ecs-core/admin/World.h"
#include "Test_class_collection.h"

namespace ecs {
struct World_test : testing::Test {
  World_test() {
    auto& entt_manager = w.get_entity_manager();
    auto& comp_admin = entt_manager.get_component_admin();
    comp_admin.add_manager(create_component_manager<C_0>(100));
    comp_admin.add_manager(create_component_manager<C_1>(300));
    comp_admin.add_manager(create_component_manager<C_2>(999));
  }

  World w;
};

TEST_F(World_test, add_system) {
  auto& ett_man = w.get_entity_manager();
  auto s_0 = std::make_unique<I_system>(ett_man);
  s_0->add_required_component<C_0>();
  s_0->add_required_component<C_1>();
  s_0->add_required_component<C_2>();
  w.add_system(std::move(s_0));
  auto s_1 = std::make_unique<I_system>(ett_man);
  s_1->add_required_component<C_0>();
  EXPECT_EQ(s_1->get_component_mask(), Component_mask{type_of<C_0>()});
  w.add_system(std::move(s_1));
  w.update(0);
}

}  // namespace ecs