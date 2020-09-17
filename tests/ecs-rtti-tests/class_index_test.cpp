#include <ecs-rtti/class_index.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdlib>

namespace ecs {
namespace rtti {

using U = ClassIndex::IndexType;
struct ClassIndexTest : testing::Test {
  ClassIndexTest() {
    srand(time(nullptr));
    for (auto& u : arr) {
      u = rand();
    }
  }

  static constexpr std::size_t kArrSize = 8888;
  std::array<U, kArrSize> arr{};
  U max = ~U(0);
};

TEST_F(ClassIndexTest, DefaultConstructor) { EXPECT_EQ(ClassIndex(), max); }

TEST_F(ClassIndexTest, Constructor) {
  for (auto u : arr) {
    EXPECT_EQ(ClassIndex(u), u);
  }
}

TEST_F(ClassIndexTest, IsAssigned) {
  EXPECT_FALSE(IsAssigned(ClassIndex()));
  for (auto u : arr) {
    EXPECT_TRUE(IsAssigned(ClassIndex(u)));
  }
}

}  // namespace rtti
}  // namespace ecs
