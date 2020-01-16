#include "pch.h"
#include "ecs-core/admin/Component_manager_admin.h"
#include "Test_class_collection.h"

namespace ecs {
struct Component_admin_test : testing::Test {
  Component_manager_admin admin;
};

TEST_F(Component_admin_test, get_manager)
{
  try {
    auto& m = admin.get_manager<C_0>();
    m;
  } catch (const std::exception&) {
    SUCCEED();
  }
}

TEST_F(Component_admin_test, add_manager) { 
  auto m_c = create_component_manager<C_0>(10);
  auto m_c_add = m_c.get();
  admin.add_manager(std::move(m_c));
  auto& m_g = admin.get_manager<C_0>();
  EXPECT_EQ(m_c_add, &m_g);
}

TEST_F(Component_admin_test, remove_manager) {

}

}