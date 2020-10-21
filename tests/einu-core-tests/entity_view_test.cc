#include <einu-core/entity_view.h>
#include <gtest/gtest.h>

#include <array>

#include "xnents.h"

namespace einu {

struct ComponentIteratorTest : public testing::Test {
  ComponentIteratorTest() {
    for (auto i = std::size_t{0}; i != kCompCount; ++i) {
      c0s[i].value = (int)i;
      c1s[i].value = (int)i + 0.5f;
      vec.push_back(&c0s[i]);
      vec.push_back(&c1s[i]);
    }
  }

  using Itr = ComponentIterator<XnentList<C0, C1>>;
  static constexpr std::size_t kCompCount = 10;
  std::array<C0, kCompCount> c0s;
  std::array<C1, kCompCount> c1s;
  std::vector<Xnent*> vec;
};

TEST_F(ComponentIteratorTest, dereference_gives_correct_value) {
  auto it = Itr{vec.begin()};
  auto&& [c0, c1] = *it;
  EXPECT_EQ(c0.value, c0s[0].value);
  EXPECT_FLOAT_EQ(c1.value, c1s[0].value);
}

TEST_F(ComponentIteratorTest, pre_increment) {
  auto it = Itr{vec.begin()};
  auto&& [c0, c1] = *++it;
  EXPECT_EQ(c0.value, c0s[1].value);
  EXPECT_FLOAT_EQ(c1.value, c1s[1].value);
}

}  // namespace einu