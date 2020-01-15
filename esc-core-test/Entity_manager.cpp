#include "pch.h"
#include "ecs-core/manager/Entity_manager.h"
#include "ecs-core/component/I_component.h"
#include "Test_component.h"

namespace ecs {
struct Entity_manager_test : testing::Test {
  Entity_manager_test()
      : manager([] {
        auto comp_admin = std::make_unique<Component_admin>();
        comp_admin->add_manager(create_component_manager<C_0>(100));
        comp_admin->add_manager(create_component_manager<C_1>(400));
        return comp_admin;
      }()) {}

  Entity_manager manager;
};

TEST_F(Entity_manager_test, spawn_entity) {
  for (auto i = std::size_t(); i != 10; ++i) {
    auto e = manager.spawn_entity();
    EXPECT_EQ(e->id(), i);
  }
}

TEST_F(Entity_manager_test, add_component) {
  algo::repeat(100, [&] {
    auto e = manager.spawn_entity();
    auto c = e.add_component<C_1>();
    auto owner = c.get_owner();
    EXPECT_EQ(owner.id(), e->id());
    EXPECT_EQ(type_of<std::remove_reference<decltype(*c)>::type>(),
              type_of<C_1>());
  });
}

TEST_F(Entity_manager_test, get_component) {
  auto e = manager.spawn_entity();
  auto c = e.get_component<C_0>();
  EXPECT_EQ(c.has_value(), false);
  auto c_0 = e.add_component<C_0>();
  auto ec_0 = e.get_component<C_0>();
  EXPECT_EQ(ec_0.has_value(), true);
  EXPECT_EQ(&(*(ec_0.value())), &(*c_0));
}

TEST_F(Entity_manager_test, remove_component) {
  auto e = manager.spawn_entity();
  e.add_component<C_0>();
  auto c = e.get_component<C_0>();
  EXPECT_EQ(c.has_value(), true);
  e.remove_component<C_0>();
  auto c_a = e.get_component<C_0>();
  EXPECT_EQ(c_a.has_value(), false);
}

}  // namespace ecs