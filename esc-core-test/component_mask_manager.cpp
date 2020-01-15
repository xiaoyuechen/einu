#include "pch.h"
#include "Test_class_collection.h"
#include "ecs-core/manager/Component_mask_manager.h"

namespace ecs {
struct Component_mask_manager_test : testing::Test {
  Entity_id e;
  Component_mask_manager m;
};

TEST_F(Component_mask_manager_test, add) {
  m.add<C_0>(e);
  EXPECT_EQ(m.has_components<C_0>(e), true);
  EXPECT_EQ(m.has_components<C_1>(e), false);
  m.add<C_1>(e);
  auto has = m.has_components<C_0, C_1>(e);
  EXPECT_EQ(has, true);
}

}  // namespace ecs