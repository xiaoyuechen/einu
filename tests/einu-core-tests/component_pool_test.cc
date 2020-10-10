#include <einu-core/internal/component_pool.h>
#include <gtest/gtest.h>

#include "xnents.h"

namespace einu {
namespace internal {

using ComponentList = XnentList<C0, C1, C2, C3, C4>;
using Pool = ComponentPool<ComponentList>;

struct ComponentPoolTest : public testing::Test {
  Pool pool;
  ComponentPoolPolicy<C0> plc0{666, C0{}};
};

TEST_F(ComponentPoolTest, can_add_policy) {
  pool.AddPolicy(plc0, XnentTypeID{0});
  EXPECT_EQ(pool.OnePoolSize<C0>(XnentTypeID{0}), 666);
}

}  // namespace internal
}  // namespace einu