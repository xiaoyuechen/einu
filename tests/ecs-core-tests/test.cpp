#include <ecs-core/ecs_engine.h>
#include <gtest/gtest.h>
#include <ecs-core/h.h>

namespace ecs {

TEST(ComponentTest, CanCreate) {
  auto l = ComponentList<>{};
  EXPECT_EQ(&l, &l);
}

}  // namespace ecs