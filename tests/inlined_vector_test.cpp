
#include <einu-engine/utility/container/inlined_vector.h>

namespace einu {

struct InlinedVectorTest : testing::Test {
  static constexpr std::size_t cap = 666;
  InlinedVector<int, cap> vec{1, 2, 8, 9};
};

TEST_F(InlinedVectorTest, Construct) { EXPECT_EQ(vec[3], 9); }

TEST_F(InlinedVectorTest, Emplace) {
  vec.emplace(vec.begin() + 1, 6);
  EXPECT_EQ(vec[1], 6);
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec[3], 8);
  EXPECT_EQ(vec[4], 9);
  EXPECT_EQ(vec.size(), 5);
}

TEST_F(InlinedVectorTest, Front) { EXPECT_EQ(vec.front(), 1); }
TEST_F(InlinedVectorTest, Back) { EXPECT_EQ(vec.back(), 9); }
TEST_F(InlinedVectorTest, Data) { EXPECT_EQ(vec.data(), &vec.front()); }
TEST_F(InlinedVectorTest, Iter) {
  EXPECT_EQ(vec.end(), vec.begin() + vec.size());
}

TEST_F(InlinedVectorTest, Empty) {
  EXPECT_EQ(vec.empty(), false);
  vec.clear();
  EXPECT_EQ(vec.empty(), true);
}

TEST_F(InlinedVectorTest, Cap) { EXPECT_EQ(vec.capacity(), cap); }

TEST_F(InlinedVectorTest, InsertRange) {
  int arr[] = {7, 5, 7};
  vec.insert(vec.begin() + 1, std::begin(arr), std::end(arr));
  EXPECT_EQ(vec.size(), 7);
  for (std::size_t i = 1; i != 4; ++i) {
    EXPECT_EQ(vec[i], arr[i - 1]);
  }
}

TEST_F(InlinedVectorTest, Erase) {
  vec.erase(vec.begin(), vec.begin() + 2);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 8);
  EXPECT_EQ(vec[1], 9);
}


}  // namespace einu
