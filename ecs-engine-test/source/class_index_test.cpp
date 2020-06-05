#include "pch.h"
// pre-compiled header

#include <ecs-engine/core/i_component.h>
#include <ecs-engine/utility/rtti/class_index_register.h>

#include <typeinfo>

namespace ecs {
using namespace rtti;
TEST(ClassIndexTest, Construct) { EXPECT_EQ(ClassIndex(), ~std::size_t(0)); }

TEST(ClassIndexTest, Algorithmic) {
  auto idx = ClassIndex(666);
  idx++;
  EXPECT_EQ(idx, 667);
}

TEST(ClassIndexTest, Compare) {
  auto idx = ClassIndex(666);
  EXPECT_EQ(idx, ClassIndex(666));
}

class C1 : public IComponent {
 public:
  int val = 0;
};
class C2 : public IComponent {};
TEST(RegisterIndex, Reg) {
  auto reg = ClassIndexRegister();
  reg.Register<C1>(ClassIndex(0));
  reg.Register<C2>(ClassIndex(1));
  EXPECT_EQ(GetClassIndex<C1>(), ClassIndex(0));
  EXPECT_EQ(GetClassIndex<C2>(), ClassIndex(1));
}

}  // namespace ecs
