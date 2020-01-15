#include "pch.h"
#include "ecs-core/manager/Entity_manager.h"
#include "ecs-core/component/I_component.h"

namespace ecs {

namespace {
struct C1 : public I_component {};
struct C2 : public I_component {};
struct C3 : public I_component {};

template<typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
  size_t pool_size)
{
  auto p = std::make_unique<typename Component_manager<T>::Pool>(pool_size);
  auto m = std::make_unique<Component_manager<T>>(std::move(p));
  return m;
}
}  // namespace

struct Entity_manager_test : testing::Test {
  Entity_manager_test() {
    manager.add_component_manager(std::move(create_component_manager<C1>(100)));
    manager.add_component_manager(std::move(create_component_manager<C2>(100)));
    manager.add_component_manager(std::move(create_component_manager<C3>(100)));
  }
  EntityManager manager;
};

TEST_F(Entity_manager_test, spawn_entity) {
  for (auto i = std::size_t(); i != 10; ++i) {
    auto e = manager.spawn_entity();
    EXPECT_EQ(e->id(), i);
  }
}

TEST_F(Entity_manager_test, add_component_handle) {
  algo::repeat(100, [&] {
    auto e = manager.spawn_entity();
    auto c = e.add_component<C1>();
    auto owner = c.get_owner();
    EXPECT_EQ(owner.id(), e->id());
    EXPECT_EQ(type_of<std::remove_reference<decltype(*c)>::type>(), type_of<C1>());
  });
}


}  // namespace ecs