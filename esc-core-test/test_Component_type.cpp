#include "pch.h"
#include "ecs-core/components/Component_type.h"

namespace {
struct Comp_a {
};

struct Comp_b {
};
}

TEST(ComponentType, Construct)
{
  using namespace ecs;
  auto type_a = type_of<Comp_a>();
  EXPECT_EQ(type_a.id(), 0);
  auto type_b = type_of<Comp_b>();
  EXPECT_EQ(type_b.id(), 1);
  EXPECT_EQ(type_a.id(), 0);
}