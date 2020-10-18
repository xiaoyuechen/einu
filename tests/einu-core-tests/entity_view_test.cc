#include <einu-core/entity_view.h>
#include <gtest/gtest.h>

#include "mock_entity.h"
#include "xnents.h"

namespace einu {

TEST(EntityView, c) {
  MockEntity ett;

  C0 comp0;
  C1 comp1;

  ett.AddComponent<C0>(comp0);
  ett.AddComponent<C1>(comp1);

  using ::testing::_;
  using ::testing::ReturnRef;

  auto view = EntityView<XnentList<C0, C1>>(ett);
  {
    EXPECT_CALL(ett, GetComponentImpl(_))
        .WillOnce(ReturnRef(comp0))
        .WillOnce(ReturnRef(comp1));
    auto&& [c0, c1] = view();
    EXPECT_EQ(c0.value, 0);
    EXPECT_FLOAT_EQ(c1.value, 0.0f);
  }
  {
    EXPECT_CALL(ett, GetComponentImpl(_))
        .WillOnce(ReturnRef(comp0))
        .WillOnce(ReturnRef(comp1));
    auto&& [c0, c1] = view();
    c0.value = 666;
    c1.value = 99.9f;
  }
  {
    EXPECT_CALL(ett, GetComponentImpl(_))
        .WillOnce(ReturnRef(comp0))
        .WillOnce(ReturnRef(comp1));
    auto&& [c0, c1] = view();
    EXPECT_EQ(c0.value, 666);
    EXPECT_FLOAT_EQ(c1.value, 99.9f);
  }
}

}  // namespace einu
