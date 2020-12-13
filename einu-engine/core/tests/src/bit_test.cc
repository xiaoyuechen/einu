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
    {~0lu, 0},
    {0b1lu << 30, 1},
    {0x0200fffflu, 6},
    {0b1, 31},
};

struct CountLeftZero32Test
    : public testing::TestWithParam<MaskExpect<uint32_t>> {};

TEST_P(CountLeftZero32Test, Test) {
  auto& mask_data = GetParam();
  EXPECT_EQ(mask_data.clz, CountLeftZero(mask_data.mask));
}

INSTANTIATE_TEST_SUITE_P(, CountLeftZero32Test,
                         testing::ValuesIn(k32MaskExpects));

}  // namespace util
}  // namespace einu
