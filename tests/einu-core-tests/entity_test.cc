#include <einu-core/einu_core.h>
#include <einu-core/internal/entity.h>
#include <gtest/gtest.h>

namespace einu {

struct C0 : Xnent {};
struct C1 : Xnent {};
struct C2 : Xnent {};
struct C3 : Xnent {};

using CL = XnentList<C0, C1, C2, C3>;
using NL = NeedList<CL, XnentList<>>;
using TestEnginePolicy = EnginePolicy<NL>;
using TestEngine = EinuEngine<TestEnginePolicy>;
using Entity = internal::Entity<tmp::Size<CL>::value>;

struct EntityTest : public testing::Test {
  EntityTest()
      : entity(0, mask, table) {}

  TestEngine engine;
  C0 c0;
  C1 c1;
  C2 c2;
  C3 c3;
  Entity::StaticXnentMask mask;
  Entity::ComponentTable table{};
  Entity entity;
};

TEST_F(EntityTest, can_add_component) {
  EXPECT_FALSE(entity.HasComponents(XnentList<C0>{}));
  entity.AddComponent(c0);
  EXPECT_TRUE(entity.HasComponents(XnentList<C0>{}));
  entity.AddComponent(c1);
  EXPECT_TRUE(entity.HasComponents(XnentList<C0, C1>{}));
  entity.AddComponent(c3);
  EXPECT_TRUE(entity.HasComponents(XnentList<C0, C1, C3>{}));
}

TEST_F(EntityTest, can_remove_component) {
  entity.AddComponent(c0);
  EXPECT_TRUE(entity.HasComponents(XnentList<C0>{}));
  auto& lc0 = entity.RemoveComponent<C0>();
  EXPECT_FALSE(entity.HasComponents(XnentList<C0>{}));
  EXPECT_EQ(&lc0, &c0);
}

TEST_F(EntityTest, can_get_id) {
  EXPECT_EQ(entity.GetID(), 0);
  auto e = Entity(666, mask, table);
  EXPECT_EQ(e.GetID(), 666);
}

}  // namespace einu