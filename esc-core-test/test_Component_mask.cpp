#include "pch.h"
#include "ecs-core/components/Component_mask.h"

TEST(ComponentMask, Construct)
{
  using namespace ecs;
  auto mask = Component_mask{ type_of<int>(), type_of<float>(), type_of<double>() };
  EXPECT_EQ(mask.get_max_type(), 512);

  auto mask_d = Component_mask();
  EXPECT_EQ(mask_d.get_max_type(), 512);
}

TEST(ComponentMask, Operator)
{
  using namespace ecs;
  auto mask = Component_mask{ type_of<int>(), type_of<float>(), type_of<double>() };
  EXPECT_EQ(mask.get_max_type(), 512);

  auto mask_d = Component_mask();
  EXPECT_EQ(mask_d.get_max_type(), 512);

  EXPECT_EQ(mask_d == mask, false);
  EXPECT_EQ(mask & mask_d, mask_d);
  EXPECT_EQ(mask | mask_d, mask);
}