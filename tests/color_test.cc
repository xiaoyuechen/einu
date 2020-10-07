#include <einu-engine/graphics/color.h>
#include <gtest/gtest.h>

namespace einu {

TEST(Color, GetScaled) {
  using Color = Color<>;
  constexpr auto c = Color{255, 34, 100, 0};
  auto n = c.GetScaled(1.f / 255.f);
  EXPECT_FLOAT_EQ(n.R(), 1.f);
  EXPECT_FLOAT_EQ(n.G(), 34.f / 255.f);
  EXPECT_FLOAT_EQ(n.B(), 100.f / 255.f);
  EXPECT_FLOAT_EQ(n.A(), 0.f / 255.f);
}

TEST(Color, ScaleZeroOne) {
  using Color = Color<std::size_t>;
  auto c = Color{255, 34, 100, 0};
  auto n = ScaleZeroOne(c, 1000);
  EXPECT_FLOAT_EQ(n.G(), 0.034f);
}

TEST(Color, RGBA) {
  using Color = Color<>;
  constexpr auto c = Color{255, 34, 100, 0};
  EXPECT_EQ(c.R(), 255);
}

}  // namespace einu
