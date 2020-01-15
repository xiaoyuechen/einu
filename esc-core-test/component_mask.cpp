#include "pch.h"
#include "ecs-core/component/Component_mask.h"

namespace ecs {
namespace {
struct S1:I_component {};
struct S2:I_component {};
struct S3:I_component {};
struct S4:I_component {};
struct S5:I_component {};
struct S6:I_component {};
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


}