#include <ecs-rtti/class_index_register.h>
#include <gtest/gtest.h>

namespace ecs {
namespace rtti {

using U = ClassIndex::IndexType;

struct ClassIndexRegisterTest : testing::Test {
  ClassIndexRegister reg;
  ClassIndex char_idx = ClassIndex(0);
  ClassIndex int_idx = ClassIndex(666);
  ClassIndex float_idx = ClassIndex(999);
};

TEST_F(ClassIndexRegisterTest, Register) {
  EXPECT_NE(GetClassIndex<char>(), char_idx);
  reg.Register<char>(char_idx);
  EXPECT_EQ(GetClassIndex<char>(), char_idx);
}

TEST_F(ClassIndexRegisterTest, GetRegisteredCount) {
  EXPECT_EQ(reg.GetRegisteredCount(), 0);
  reg.Register<char>(char_idx);
  EXPECT_EQ(reg.GetRegisteredCount(), 1);
}

}  // namespace rtti
}  // namespace ecs
