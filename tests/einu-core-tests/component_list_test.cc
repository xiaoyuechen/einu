#include <einu-core/internal/component_index_list.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

struct MockComponent1 : IComponent {
  int v = -1;
};

struct MockComponent2 : IComponent {
  int v = -1;
};

TEST(ComponentIndexList, _) {
  SetComponentIndex<MockComponent1>(ComponentIndex(1));
  SetComponentIndex<MockComponent2>(ComponentIndex(2));
  using CL = ComponentList<MockComponent1, MockComponent2>;
  auto idxl = ComponentIndexList(CL());
  EXPECT_EQ(*idxl.begin(), 1);
  EXPECT_EQ(*(idxl.begin() + 1), 2);
}

TEST(GetComponentIndexList, _) {
  SetComponentIndex<MockComponent1>(ComponentIndex(1));
  SetComponentIndex<MockComponent2>(ComponentIndex(2));
  using CL = ComponentList<MockComponent1, MockComponent2>;
  auto idxl = GetComponentIndexList(CL());
  EXPECT_EQ(*idxl.begin(), 1);
  EXPECT_EQ(*(idxl.begin() + 1), 2);
}

}  // namespace internal
}  // namespace einu