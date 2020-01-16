#include "pch.h"
#include "ecs-core/component/Component_type.h"

namespace ecs {
namespace {
struct Comp_a : Component{};
struct Comp_b : Component{};
}
TEST(ComponentType, Construct)
{
  auto type_a = type_of<Comp_a>();
  auto type_b = type_of<Comp_b>();
  EXPECT_EQ(type_a==type_b, false);
}
}