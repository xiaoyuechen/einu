#include "pch.h"
#include "ecs-core/component/Component_mask.h"

namespace ecs {
namespace {
struct S1:Component {};
struct S2:Component {};
struct S3:Component {};
struct S4:Component {};
struct S5:Component {};
struct S6:Component {};
}

namespace {
struct Test_component_mask : public testing::Test {
  Test_component_mask()
  {
    mask_arr.push_back(Component_mask{ type_of<S1>() });
    mask_arr.push_back(Component_mask{ type_of<S2>() });
    mask_arr.push_back(Component_mask{ type_of<S2>(), type_of<S1>() });
    mask_arr.push_back(Component_mask{ type_of<S2>(), type_of<S1>(), type_of<S3>() });
    mask_arr.push_back(Component_mask{ type_of<S5>() });
  }
  std::vector<Component_mask> mask_arr;
};
}

TEST_F(Test_component_mask, bit_wise_and)
{
  EXPECT_EQ(mask_arr[0] & mask_arr[1], Component_mask());
  EXPECT_EQ(mask_arr[0] & mask_arr[2], Component_mask{ type_of<S1>() });
  EXPECT_EQ(mask_arr[2] & mask_arr[0], Component_mask{ type_of<S1>() });
  auto e = Component_mask{ type_of<S1>(), type_of<S2>() };
  EXPECT_EQ(mask_arr[2] & mask_arr[3], e);
}

TEST_F(Test_component_mask, and_eq) {
  EXPECT_EQ(mask_arr[0] &= mask_arr[1], Component_mask());
  EXPECT_EQ(mask_arr[0] &= mask_arr[2], Component_mask());
  EXPECT_EQ(mask_arr[1] &= mask_arr[2], Component_mask{type_of<S2>()});
}
}