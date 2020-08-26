#include "pch.h"
// pre-compiled header

#include <ecs-engine/graphics/color.h>

#include <typeinfo>

namespace ecs {

TEST(Color, GetScaled) {
  using Color = Color<>;
  auto c = Color{255, 34, 100, 0};
  auto n = c.GetScaled(1.f / 255.f);
  EXPECT_EQ(n.R(), 1.f);
  EXPECT_EQ(n.G(), 34.f / 255.f);
}

TEST(Color, ScaleZeroOne) {
  using Color = Color<std::size_t>;
  auto c = Color{255, 34, 100, 0};
  auto n = ScaleZeroOne(c, 1000);
  EXPECT_EQ(n.G(), 0.034f);
}

}  // namespace ecs
