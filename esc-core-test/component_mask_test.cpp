#include "pch.h"
// pre-compiled header

#include "Test_class_collection.h"
#include "ecs-core/component_mask.h"

namespace ecs {

struct ComponentMaskTest : testing::Test {
  ComponentMaskTest()
      : sig{GetComponentTypeIndex<C_0>(), GetComponentTypeIndex<C_1>()} {}
  ComponentMask sig;
};

TEST_F(ComponentMaskTest, Equal) {
  auto e = ComponentMask{GetComponentTypeIndex<C_0>(),
                                GetComponentTypeIndex<C_1>()};
  EXPECT_EQ(sig == e, true);

  e = ComponentMask{GetComponentTypeIndex<C_0>()};

  EXPECT_EQ(sig == e, false);
}

TEST_F(ComponentMaskTest, NotEqual) {
  auto e =
      ComponentMask{GetComponentTypeIndex<C_0>(), GetComponentTypeIndex<C_1>()};
  EXPECT_EQ(sig != e, false);

  e = ComponentMask{GetComponentTypeIndex<C_0>()};

  EXPECT_EQ(sig != e, true);
}
}  // namespace ecs