#include <einu-engine/core/internal/xnent_type_id_register.h>
#include <gtest/gtest.h>

#include "xnents.h"

namespace einu {
namespace internal {

TEST(XnentTypeIDRegisterTest, _) {
  using XnentList = XnentList<C0, C1, C2>;

  {
    XnentTypeIDRegister<XnentList> reg;
    EXPECT_EQ(GetXnentTypeID<C0>(), 0);
    EXPECT_EQ(GetXnentTypeID<C1>(), 1);
    EXPECT_EQ(GetXnentTypeID<C2>(), 2);
  }

  EXPECT_EQ(GetXnentTypeID<C0>(), XnentTypeID{});
  EXPECT_EQ(GetXnentTypeID<C1>(), XnentTypeID{});
  EXPECT_EQ(GetXnentTypeID<C2>(), XnentTypeID{});
}

}  // namespace internal
}  // namespace einu
