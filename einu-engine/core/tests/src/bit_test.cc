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

#include "einu-engine/core/util/bit.h"

#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

namespace einu {
namespace util {

template <typename Mask>
struct MaskExpect {
  Mask mask;
  int clz;
};

static constexpr MaskExpect<uint64_t> k64MaskExpects[] = {
    {~0llu, 0},
    {0b1llu << 62, 1},
    {0b001011llu << 58, 2},
    {0b1, 63},
};

struct CountLeftZero64Test
    : public testing::TestWithParam<MaskExpect<uint64_t>> {};

TEST_P(CountLeftZero64Test, Test) {
  auto& mask_data = GetParam();
  EXPECT_EQ(mask_data.clz, CountLeftZero(mask_data.mask));
}

INSTANTIATE_TEST_SUITE_P(CountLeftZeroTest, CountLeftZero64Test,
                         testing::ValuesIn(k64MaskExpects));

static constexpr MaskExpect<uint32_t> k32MaskExpects[] = {
    {~0u, 0},
    {0b1u << 30, 1},
    {0x0200ffffu, 6},
    {0b1u, 31},
};

struct CountLeftZero32Test
    : public testing::TestWithParam<MaskExpect<uint32_t>> {};

TEST_P(CountLeftZero32Test, Test) {
  auto& mask_data = GetParam();
  EXPECT_EQ(mask_data.clz, CountLeftZero(mask_data.mask));
}

INSTANTIATE_TEST_SUITE_P(CountLeftZeroTest, CountLeftZero32Test,
                         testing::ValuesIn(k32MaskExpects));

template <typename Mask>
struct RangeMaskExpect {
  std::vector<Mask> masks;
  std::optional<int> clz;
};

static const RangeMaskExpect<std::uint64_t> kRangeMask64Expects[] = {
    {{0x0}, std::nullopt},
    {{0x0, 0x0, 0x0}, std::nullopt},
    {{0x0, 0x0, 0x1, 0xfff}, 64 * 3 - 1},
    {{0x0, 0x1ull << 63, 0x0, 0x0, 0xf}, 64},
    {{0x1ull << 63, 0x0, 0x0, 0xf}, 0}};

struct CountLeftZeroRange64Test
    : public testing::TestWithParam<RangeMaskExpect<std::uint64_t>> {};

TEST_P(CountLeftZeroRange64Test, Test) {
  auto& range_mask_expect = GetParam();
  auto begin = range_mask_expect.masks.data();
  auto end = begin + range_mask_expect.masks.size();
  EXPECT_EQ(range_mask_expect.clz, CountLeftZero(begin, end));
}

INSTANTIATE_TEST_SUITE_P(CountLeftZeroTest, CountLeftZeroRange64Test,
                         testing::ValuesIn(kRangeMask64Expects));

static const RangeMaskExpect<std::uint32_t> kRangeMask32Expects[] = {
    {{0x0}, std::nullopt},
    {{0x0, 0x0, 0x0}, std::nullopt},
    {{0x0, 0x0, 0x1, 0xfff}, 32 * 3 - 1},
    {{0x0, 0x1u << 31, 0x0, 0x0, 0xf}, 32},
    {{0x1u << 31, 0x0, 0x0, 0xf}, 0}};

struct CountLeftZeroRange32Test
    : public testing::TestWithParam<RangeMaskExpect<std::uint32_t>> {};

TEST_P(CountLeftZeroRange32Test, Test) {
  auto& range_mask_expect = GetParam();
  auto begin = range_mask_expect.masks.data();
  auto end = begin + range_mask_expect.masks.size();
  EXPECT_EQ(range_mask_expect.clz, CountLeftZero(begin, end));
}

INSTANTIATE_TEST_SUITE_P(CountLeftZeroTest, CountLeftZeroRange32Test,
                         testing::ValuesIn(kRangeMask32Expects));

struct BitVectorInitTestExpect {
  std::size_t count;
  bool value;
};

struct BitVectorInitTest
    : public testing::TestWithParam<BitVectorInitTestExpect> {};

TEST_P(BitVectorInitTest, Test) {
  auto [count, value] = GetParam();
  auto vec = BitVector(count, value);
  EXPECT_EQ(vec.size(), count);
  if (count == 0) {
    EXPECT_EQ(vec.countl_zero(), std::nullopt);
  } else {
    if (value) {
      EXPECT_EQ(vec.countl_zero(), 0);
    } else {
      EXPECT_EQ(vec.countl_zero(), std::nullopt);
    }
  }
}

static constexpr const BitVectorInitTestExpect kBitVectorInitTestExpects[] = {
    {0, false}, {0, true}, {66, false}, {66, true}, {999, false}, {999, true}};

INSTANTIATE_TEST_SUITE_P(BitVectorTest, BitVectorInitTest,
                         testing::ValuesIn(kBitVectorInitTestExpects));

struct BitVectorSetResetTest
    : public testing::TestWithParam<std::vector<std::size_t>> {
  BitVector vec{1000, false};
};

TEST_P(BitVectorSetResetTest, Test) {
  auto poses = GetParam();
  for (auto pos : poses) {
    EXPECT_FALSE(vec.test(pos));
    vec.set(pos);
    EXPECT_TRUE(vec.test(pos));
  }

  for (auto pos : poses) {
    EXPECT_TRUE(vec.test(pos));
  }

  for (auto pos : poses) {
    vec.reset(pos);
    EXPECT_FALSE(vec.test(pos));
  }

  for (auto pos : poses) {
    EXPECT_FALSE(vec.test(pos));
  }
}

static const std::vector<std::size_t> kBitVectorSetResetTestData[] = {
    {0, 1, 2, 3, 4}, {0, 64, 128}, {62, 63, 64, 65}, {568, 2, 999, 833}};

INSTANTIATE_TEST_SUITE_P(BitVectorTest, BitVectorSetResetTest,
                         testing::ValuesIn(kBitVectorSetResetTestData));

TEST(BitVectorTest, ResizeDown) {
  auto vec = BitVector(120, false);
  vec.set(63);
  vec.resize(64);
  EXPECT_EQ(vec.size(), 64);
  EXPECT_TRUE(vec.test(63));
  EXPECT_FALSE(vec.test(62));
  EXPECT_EQ(vec.countl_zero(), 63);
}

TEST(BitVectorTest, ResizeUp) {
  auto vec = BitVector(120, false);
  vec.set(119);
  EXPECT_TRUE(vec.test(119));
  vec.resize(150);
  EXPECT_EQ(vec.size(), 150);
  EXPECT_FALSE(vec.test(118));
  EXPECT_TRUE(vec.test(119));
  EXPECT_FALSE(vec.test(120));
  EXPECT_FALSE(vec.test(149));
  EXPECT_EQ(vec.countl_zero(), 119);
}

}  // namespace util
}  // namespace einu
