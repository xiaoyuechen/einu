#include <einu-util/object_pool.h>
#include <gtest/gtest.h>

namespace einu {
namespace util {

struct FixedPoolTest : testing::Test {
  static constexpr std::size_t kSize = 100;
  FixedPool<int> pool{kSize};
};

TEST_F(FixedPoolTest, a_new_pool_is_free) {
  EXPECT_EQ(pool.FreePos(), 0);
  EXPECT_FALSE(AllAcquired(pool));
}

TEST_F(FixedPoolTest, pool_size_is_fixed) {
  EXPECT_EQ(pool.Size(), kSize);
  auto acquired = std::vector<decltype(pool)::value_type*>{kSize};
  std::for_each(acquired.begin(), acquired.end(), [&](auto&& v) {
    v = &pool.Acquire();
    EXPECT_EQ(pool.Size(), kSize);
  });

  std::for_each(acquired.begin(), acquired.end(), [&](auto&& v) {
    pool.Release(*v);
    EXPECT_EQ(pool.Size(), kSize);
  });
}

TEST_F(FixedPoolTest, free_pos_move_right_after_acquire) {
  auto acquired = std::vector<decltype(pool)::value_type*>{kSize};
  auto pre_free_pos = pool.FreePos();
  std::for_each(acquired.begin(), acquired.end(), [&](auto&& v) {
    v = &pool.Acquire();
    auto free_pos = pool.FreePos();
    EXPECT_TRUE(pre_free_pos < free_pos);
    pre_free_pos = free_pos;
  });
  EXPECT_TRUE(AllAcquired(pool));
}

}  // namespace util
}  // namespace einu