#include "pch.h"
// pre-compiled header
#include <type_traits>

#include "Test_class_collection.h"
#include "ecs-engine/window/context.h"
#include "ecs-engine/window/window.h"
#include "ecs-engine/core/component_setting.h"
#include "ecs-engine/core/entity_manager.h"
#include "ecs-engine/core/system.h"
#include "ecs-engine/core/threading_model.h"
#include "ecs-engine/utility/type_list.h"

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
// EntityManagerTest:
//////////////////////////////////////////////////////////////////////////

using MyComponentList = ComponentList<C_0, C_1, C_2>;
using MyComponentSetting = ComponentSetting<MyComponentList>;

class MyComponentManagerPolicy
    : public ComponentManagerPolicy<MyComponentSetting, MultiThreaded> {
 public:
  MyComponentManagerPolicy()
      : c_0_manager_{99}
      , c_1_manager_{666}
      , c_2_manager_{99999}
      , ComponentManagerPolicy(c_0_manager_, c_1_manager_, c_2_manager_) {}

 private:
  ComponentManager<C_0> c_0_manager_;
  ComponentManager<C_1> c_1_manager_;
  ComponentManager<C_2> c_2_manager_;
};

using MyEntityManager =
    EntityManager<MyComponentSetting, MyComponentManagerPolicy, MultiThreaded>;

struct EntityManagerTest : testing::Test {
  MyEntityManager ett_mgr;
};

TEST_F(EntityManagerTest, CreateEntity) {
  for (auto i = std::size_t{0}; i != 9999; ++i) {
    ett_mgr.CreateEntity();
  }
  EXPECT_EQ(ett_mgr.GetEntityCount(), 9999);
}

//////////////////////////////////////////////////////////////////////////
// SystemTest:
//////////////////////////////////////////////////////////////////////////

using MyRequiredComponentList = RequiredComponentList<C_2, C_1>;
using MySystem = System<MyEntityManager, MyRequiredComponentList>;

struct SystemTest : testing::Test {
  SystemTest()
      : sys(ett_mgr) {}

  MyEntityManager ett_mgr;
  MySystem sys;
};

TEST_F(SystemTest, GetMatchingComponentTuples) {
  EXPECT_EQ(sys.GetMatchingComponentTuples().size(), 0);
  for (auto i = std::size_t(0); i != 666; ++i) {
    auto ett = ett_mgr.CreateEntity();
    ett.AddComponent<C_1>();
    ett.AddComponent<C_2>();
  }

  EXPECT_EQ(sys.GetMatchingComponentTuples().size(), 666);

  for (auto i = std::size_t(0); i != 99; ++i) {
    auto ett = ett_mgr.CreateEntity();
    ett.AddComponent<C_0>();
  }

  EXPECT_EQ(sys.GetMatchingComponentTuples().size(), 666);
}

//////////////////////////////////////////////////////////////////////////
// WindowTest:
//////////////////////////////////////////////////////////////////////////
struct WindowTest : testing::Test {
  WindowTest()
      : window(Window::Mode::WINDOWED, 1280, 720, "application") {}
  Window window;
};

TEST_F(WindowTest, Construct) { getchar(); }

}  // namespace ecs