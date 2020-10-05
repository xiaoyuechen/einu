#include <einu-rtti/class_index_storage.h>
#include <gtest/gtest.h>

namespace einu {
namespace rtti {

template <typename T>
void TestGetClassIndex() {
  EXPECT_EQ(GetClassIndex<T>(), ClassIndex());
}

template <typename... Ts>
void TestGetClassIndice() {
  (TestGetClassIndex<Ts>(), ...);
}

TEST(ClassIndexStorageTest, GetClassIndex) {
  TestGetClassIndice<char, int, float, double, long long>();
}

}  // namespace rtti
}  // namespace einu
