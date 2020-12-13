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

INSTANTIATE_TEST_SUITE_P(, CountLeftZero64Test,
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

INSTANTIATE_TEST_SUITE_P(, CountLeftZero32Test,
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

INSTANTIATE_TEST_SUITE_P(, CountLeftZeroRange64Test,
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

INSTANTIATE_TEST_SUITE_P(, CountLeftZeroRange32Test,
                         testing::ValuesIn(kRangeMask32Expects));

}  // namespace util
}  // namespace einu
