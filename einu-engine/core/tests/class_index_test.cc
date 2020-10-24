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

#include <einu-engine/core/rtti/type_id.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdlib>

namespace einu {
namespace rtti {

using U = TypeID::IndexType;
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

TEST_F(ClassIndexTest, DefaultConstructor) { EXPECT_EQ(TypeID(), max); }

TEST_F(ClassIndexTest, Constructor) {
  for (auto u : arr) {
    EXPECT_EQ(TypeID(u), u);
  }
}

TEST_F(ClassIndexTest, IsAssigned) {
  EXPECT_FALSE(IsAssigned(TypeID()));
  for (auto u : arr) {
    EXPECT_TRUE(IsAssigned(TypeID(u)));
  }
}

template <typename T>
void TestGetClassIndex() {
  EXPECT_EQ(GetTypeID<T>(), TypeID());
}

template <typename... Ts>
void TestGetClassIndice() {
  (TestGetClassIndex<Ts>(), ...);
}

TEST(ClassIndexStorageTest, GetTypeID) {
  TestGetClassIndice<char, int, float, double, long long>();
}

}  // namespace rtti
}  // namespace einu
