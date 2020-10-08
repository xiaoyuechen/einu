#include <einu-core/need_list.h>
#include <gtest/gtest.h>

namespace einu {

TEST(NeedList, _) {
  using ComponentList = XnentList<Xnent>;
  using SinglenentList = XnentList<Xnent>;
  using NeedList = NeedList<ComponentList, SinglenentList>;
  auto nl = NeedList{};
  auto cl = NeedList::ComponentList{};
  EXPECT_NE(&cl, nullptr);
}

}  // namespace einu