#include "pch.h"
#include "ecs-core/Component_manager.h"
#include "Test_class_collection.h"
#include <stdexcept>

namespace ecs {
struct Component_manager_test : testing::Test {
  Component_manager_test() { manager = create_component_manager<C_0>(100); }
  std::unique_ptr<ComponentManager<C_0>> manager;
  EntityID entity{0};
};

TEST_F(Component_manager_test, get_component) {
  try {
    auto& c = manager->get_component(entity);
    c;
  } catch (std::out_of_range&) {
    SUCCEED();
  }
}
TEST_F(Component_manager_test, add_component) {
  auto& c_a = manager->add_component(entity);
  auto& c_g = manager->get_component(entity);
  EXPECT_EQ(&c_a, &c_g);
}

TEST_F(Component_manager_test, remove_component) {
  manager->add_component(entity);
  manager->remove_component(entity);
  try {
    auto& c = manager->get_component(entity);
    c;
  } catch (const std::out_of_range&) {
    SUCCEED();
  }
}
}  // namespace ecs