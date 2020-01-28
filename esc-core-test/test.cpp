#include "pch.h"
// pre-compiled header
#include <type_traits>

#include "Test_class_collection.h"
#include "ecs-core/component_setting.h"
#include "ecs-core/entity_manager.h"
#include "ecs-core/utility/type_list.h"

namespace ecs {

//////////////////////////////////////////////////////////////////////////
// TypeListTest:
//////////////////////////////////////////////////////////////////////////

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
  using AppendedList = typename Append<TypeList, C_2>::Result;
  EXPECT_EQ(Size<AppendedList>::value, 5);

  using ErasedAllList = typename EraseAll<AppendedList, C_2>::Result;
  constexpr auto size = Size<ErasedAllList>::value;
  EXPECT_EQ(size, 3);

  using SecondType = TypeAt<ErasedAllList, 2>::Type;
  constexpr auto result = std::is_same<SecondType, C_3>::value;
  EXPECT_EQ(result, true);
}

//////////////////////////////////////////////////////////////////////////
// WolrdTest:
//////////////////////////////////////////////////////////////////////////

using MyComponentList = ComponentList<C_0, C_1, C_3, C_4>;
using MyComponentSetting = ComponentSetting<MyComponentList>;

class MyComponentManagerPolicy {
 public:
  MyComponentManagerPolicy()
      : c_0_manager_{std::make_unique<FixedSizePool<C_0>>(100)}
      , c_1_manager_{std::make_unique<FixedSizePool<C_1>>(666)} {}

  const auto& GetComponentManager(Type2Type<C_0>) const { return c_0_manager_; }
  auto& GetComponentManager(Type2Type<C_0>) { return c_0_manager_; }
  const auto& GetComponentManager(Type2Type<C_1>) const { return c_1_manager_; }
  auto& GetComponentManager(Type2Type<C_1>) { return c_1_manager_; }

 private:
  ComponentManager<C_0> c_0_manager_;
  ComponentManager<C_1> c_1_manager_;
};

struct EntityManagerTest : testing::Test {
  EntityManager<MyComponentSetting, MyComponentManagerPolicy> ett_mgr;
};

TEST_F(EntityManagerTest, GetComponentManager) {
  auto& m = ett_mgr.GetComponentManager<C_1>();
  constexpr bool r = std::is_same<decltype(m), ComponentManager<C_1>&>::value;
  EXPECT_EQ(r, true);

  const auto& mgr_cref = ett_mgr;
  mgr_cref.GetComponentManager<C_1>();
}

TEST_F(EntityManagerTest, AddComponent) {
  auto eid = ett_mgr.SpawnEntity();
  ett_mgr.AddComponent<C_1>(eid);
}

TEST_F(EntityManagerTest, RemoveComponent) {
  auto eid = ett_mgr.SpawnEntity();
  ett_mgr.AddComponent<C_1>(eid);
  ett_mgr.RemoveComponent<C_1>(eid);
}

TEST_F(EntityManagerTest, GetEntity) {
  auto eid = ett_mgr.SpawnEntity();
  /*auto& ett = */ ett_mgr.GetEntity(eid);
}

TEST_F(EntityManagerTest, GetMatchingComponents) {
  ett_mgr.RegisterInterest<const C_0, const C_1>();
  auto eid = ett_mgr.SpawnEntity();
  ett_mgr.AddComponent<C_0>(eid);
  ett_mgr.AddComponent<C_1>(eid);

  auto comp_buffer = std::vector<std::tuple<C_0&, C_1&>>{};
  ett_mgr.GetMatchingComponents(comp_buffer);
}

}  // namespace ecs