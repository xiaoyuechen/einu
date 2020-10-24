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

#include <einu-engine/core/internal/xnent_mask.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

TEST(XnentMaskTest, a_new_mask_has_the_correct_size_and_bits_set_1) {
  auto sig = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  EXPECT_EQ(sig.SizeInBytes(), 1);
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), 0b110);
}

TEST(XnentMaskTest, a_new_mask_has_the_correct_size_and_bits_set_2) {
  auto sig = DynamicXnentMask{XnentTypeID(12), XnentTypeID(6)};
  EXPECT_EQ(sig.SizeInBytes(), 2);
  EXPECT_EQ(*(std::uint16_t*)sig.Data(), 0b0001000001000000);
}

TEST(XnentMaskTest, OperatorBitWiseAnd) {
  auto sig = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), 0b110);
  auto ssig = StaticXnentMask<16>{"1111111100000110"};
  auto r = sig & ssig;
  EXPECT_EQ(r.to_ulong(), 0b0000000000000110);
}

TEST(XnentMaskTest, EqualsEqualsOperator) {
  auto mask = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  auto smask = StaticXnentMask<16>{"1111111100000000"};
  EXPECT_EQ(mask & smask, StaticXnentMask<16>{});
  EXPECT_EQ(mask | smask, StaticXnentMask<16>{"1111111100000110"});
}

}  // namespace internal
}  // namespace einu
