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

struct MaskExpect {
  uint64_t mask;
  int clz;
};

static constexpr MaskExpect kMaskExpects[] = {
    {~0llu, 0},
    {0b1llu << 62, 1},
    {0b001011llu << 58, 2},
    {0b1, 63},
};

struct CountLeftZeroTest : public testing::TestWithParam<MaskExpect> {};

TEST_P(CountLeftZeroTest, Test) {
  auto& mask_data = GetParam();
  EXPECT_EQ(mask_data.clz, CountLeftZero(mask_data.mask));
}

INSTANTIATE_TEST_SUITE_P(Instance, CountLeftZeroTest,
                         testing::ValuesIn(kMaskExpects));

}  // namespace util
}  // namespace einu
