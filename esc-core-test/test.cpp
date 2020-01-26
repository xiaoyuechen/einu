#include "pch.h"
// pre-compiled header
#include "Test_class_collection.h"
#include "ecs-core/i_system.h"

namespace ecs {

class MySystem : public System<C_0, C_1, C_2> {
 public:
  virtual void Update(float) override final {
    for (auto&& t : GetComponentCache()) {
      auto [c_0, c_1, c_2] = t;
    }
  }
};

TEST(SystemTest, Construct) {
  MySystem s;
  s.Update(1);
}


//////////////////////////////////////////////////////////////////////////
// TypeListTest:
//////////////////////////////////////////////////////////////////////////

#include "ecs-core/utility/type_list.h"

struct TypeListTest : testing::Test {
  using TypeList = TypeList<C_0, C_1, C_2, C_3>;
};

TEST_F(TypeListTest, Size) { EXPECT_EQ(Size<TypeList>::value, 4); }

TEST_F(TypeListTest, TypeAt) {
  constexpr bool result = std::is_same<TypeAt<TypeList, 2>::Type, C_2>::value;
  EXPECT_EQ(result, true);
}

TEST_F(TypeListTest, IndexOf) {
  constexpr auto c0_index = IndexOf<TypeList, C_0>::value;
  EXPECT_EQ(c0_index, 0);

  constexpr auto c3_index = IndexOf<TypeList, C_3>::value;
  EXPECT_EQ(c3_index, 3);
}

TEST_F(TypeListTest, Append) {
  using AppendedList = Append<TypeList, C_4>::Result;
  EXPECT_EQ(Size<AppendedList>::value, 5);
  using BackType = typename TypeAt<AppendedList, 4>::Type;
  constexpr bool result = std::is_same<BackType, C_4>::value;
  EXPECT_EQ(result, true);
}

TEST_F(TypeListTest, Erase) {
  using ErasedList = Erase<TypeList, C_2>::Result;
  EXPECT_EQ(Size<ErasedList>::value, 3);

  using TailType = typename TypeAt<ErasedList, 2>::Type;
  constexpr bool result = std::is_same<TailType, C_3>::value;
  EXPECT_EQ(result, true);
}

TEST_F(TypeListTest, EraseAll) {
  using  AppendedList = typename Append<TypeList, C_2>::Result;
  EXPECT_EQ(Size<AppendedList>::value, 5);

  using ErasedAllList = typename EraseAll<AppendedList, C_2>::Result;
  constexpr auto size = Size<ErasedAllList>::value;
  EXPECT_EQ(size, 3);

  using SecondType = TypeAt<ErasedAllList, 2>::Type;
  constexpr auto result = std::is_same<SecondType, C_3>::value;
  EXPECT_EQ(result, true);
}
}  // namespace ecs