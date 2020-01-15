#include "pch.h"
#include "ecs-core/admin/Component_admin.h"
#include "Test_class_collection.h"

namespace ecs {
struct Component_admin_test : testing::Test {
  Component_admin_test()
  {
    admin.add_manager(create_component_manager<C_1>(100));
  }
  Component_admin admin;
};

TEST_F(Component_admin_test, get)
{
  auto m_1 = admin.get_manager<C_1>();
  EXPECT_EQ(m_1.has_value(), true);
  auto m_2 = admin.get_manager<C_2>();
  EXPECT_EQ(m_2.has_value(), false);
}

TEST_F(Component_admin_test, remove) {
  auto m = admin.get_manager<C_1>();
  EXPECT_EQ(m.has_value(), true);

  admin.remove_manager<C_1>();
  auto m_after = admin.get_manager<C_1>();
  EXPECT_EQ(m_after.has_value(), false);
}

}