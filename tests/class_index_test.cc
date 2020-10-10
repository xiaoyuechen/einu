#include <einu-engine/core/i_component.h>
#include <einu-engine/utility/rtti/class_index_register.h>

#include <typeinfo>

namespace einu {
using namespace rtti;
TEST(ClassIndexTest, Construct) { EXPECT_EQ(TypeID(), ~std::size_t(0)); }

TEST(ClassIndexTest, Algorithmic) {
  auto idx = TypeID(666);
  idx++;
  EXPECT_EQ(idx, 667);
}

TEST(ClassIndexTest, Compare) {
  auto idx = TypeID(666);
  EXPECT_EQ(idx, TypeID(666));
}

class C1 : public Xnent {
 public:
  int val = 0;
};
class C2 : public Xnent {};
TEST(RegisterIndex, Reg) {
  auto reg = ClassIndexRegister();
  reg.Register<C1>(TypeID(0));
  reg.Register<C2>(TypeID(1));
  EXPECT_EQ(GetClassIndex<C1>(), TypeID(0));
  EXPECT_EQ(GetClassIndex<C2>(), TypeID(1));
}

}  // namespace einu
