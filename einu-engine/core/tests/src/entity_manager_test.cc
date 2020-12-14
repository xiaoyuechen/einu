// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "einu-engine/core/internal/entity_manager.h"

#include "einu-engine/core/entity_view.h"
#include "einu-engine/core/internal/eid_pool.h"
#include "einu-engine/core/internal/xnent_pool.h"
#include "einu-engine/core/internal/xnent_type_id_register.h"
#include "gtest/gtest.h"
#include "src/xnents.h"

namespace einu {
namespace internal {

struct EntityManagerTest : public testing::Test {
  using TestCompList = XnentList<C0, C1, C2>;
  using TestCompPool = XnentPool<TestCompList>;
  using TestEIDPool = EIDPool;
  static constexpr std::size_t kMaxComponent = 256;
  static constexpr std::size_t kMaxSinglenent = 256;
  using EttMgr = EntityManager<kMaxComponent, kMaxSinglenent>;

  EntityManagerTest() {
    ett_mgr.SetComponentPool(comp_pool);
    ett_mgr.SetEIDPool(eid_pool);
    auto eid = ett_mgr.CreateEntity();
    ett_mgr.AddComponent<C0>(eid);
    ett_mgr.AddComponent<C1>(eid);
    ett_mgr.CreateEntity();
  }

  XnentTypeIDRegister<TestCompList> reg;
  TestCompPool comp_pool;
  TestEIDPool eid_pool;
  EttMgr ett_mgr;
};

TEST_F(
    EntityManagerTest,
    get_entities_with_components_returns_all_entities_when_comp_list_is_empty) {
  auto ett_view = EntityView<XnentList<>>{};
  ett_view.View(ett_mgr);
  EXPECT_EQ(ett_view.Size(), 2);
}

}  // namespace internal
}  // namespace einu
