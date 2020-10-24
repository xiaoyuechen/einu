// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <einu-engine/core/util/object_pool.h>
#include <gtest/gtest.h>

namespace einu {
namespace util {

struct FixedPoolTest : public testing::Test {
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

struct DynamicPoolTest : public testing::Test {
  static constexpr std::size_t kSize = 100;
  DynamicPool<int> pool{kSize};
};

TEST_F(DynamicPoolTest, pool_size_can_grow) {
  EXPECT_EQ(pool.Size(), kSize);
  auto new_size = pool.Size() * 2;
  for (std::size_t i = 0; i != kSize + 1; ++i) {
    [[maybe_unused]] auto& r = pool.Acquire();
  }
  EXPECT_EQ(pool.Size(), new_size);
}

TEST_F(DynamicPoolTest, pool_only_grows_when_full) {
  EXPECT_EQ(pool.Size(), kSize);
  for (std::size_t i = 0; i != kSize; ++i) {
    [[maybe_unused]] auto& r = pool.Acquire();
  }
  EXPECT_EQ(pool.Size(), kSize);
  auto new_size = pool.Size() * 2;
  [[maybe_unused]] auto& r = pool.Acquire();
  EXPECT_EQ(pool.Size(), new_size);
}

TEST_F(DynamicPoolTest, release_would_make_more_space_available) {
  EXPECT_EQ(pool.Size(), kSize);
  auto acquired = std::vector<decltype(pool)::value_type*>{kSize + 1};
  auto new_size = pool.Size() * 2;
  std::for_each(acquired.begin(), acquired.end(),
                [&](auto&& v) { v = &pool.Acquire(); });
  EXPECT_EQ(pool.Size(), new_size);
  std::for_each(acquired.rbegin(), acquired.rend(),
                [&](auto&& v) { pool.Release(*v); });

  acquired.resize(pool.Size());
  std::for_each(acquired.begin(), acquired.end(),
                [&](auto&& v) { v = &pool.Acquire(); });
  EXPECT_EQ(pool.Size(), new_size);
}

TEST_F(DynamicPoolTest, release_would_not_change_size) {
  EXPECT_EQ(pool.Size(), kSize);
  auto acquired = std::vector<decltype(pool)::value_type*>{kSize + 1};
  auto new_size = pool.Size() * 2;
  std::for_each(acquired.begin(), acquired.end(),
                [&](auto&& v) { v = &pool.Acquire(); });
  EXPECT_EQ(pool.Size(), new_size);
  std::for_each(acquired.rbegin(), acquired.rbegin(),
                [&](auto&& v) { pool.Release(*v); });
  EXPECT_EQ(pool.Size(), new_size);
}

}  // namespace util
}  // namespace einu
