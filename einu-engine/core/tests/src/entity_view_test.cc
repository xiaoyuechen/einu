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

#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/core/internal/entity_manager.h>
#include <einu-engine/core/internal/xnent_pool.h>
#include <einu-engine/core/internal/xnent_type_id_register.h>
#include <gtest/gtest.h>

#include <array>

#include "src/xnents.h"

namespace einu {

struct ComponentIteratorTest : public testing::Test {
  ComponentIteratorTest() {
    for (auto i = 0; i != kCompCount; ++i) {
      c0s[i].value = i;
      c1s[i].value = i + 0.5f;
      vec.push_back(&c0s[i]);
      vec.push_back(&c1s[i]);
    }
  }

  using Itr = ComponentIterator<XnentList<C0, C1>>;
  static constexpr std::size_t kCompCount = 10;
  std::array<C0, kCompCount> c0s;
  std::array<C1, kCompCount> c1s;
  std::vector<Xnent*> vec;
};

TEST_F(ComponentIteratorTest, dereference_gives_correct_value) {
  auto it = Itr{vec.begin()};
  auto&& [c0, c1] = *it;
  EXPECT_EQ(c0.value, c0s[0].value);
  EXPECT_FLOAT_EQ(c1.value, c1s[0].value);
}

TEST_F(ComponentIteratorTest, pre_increment) {
  auto it = Itr{vec.begin()};
  auto&& [c0, c1] = *++it;
  EXPECT_EQ(c0.value, c0s[1].value);
  EXPECT_FLOAT_EQ(c1.value, c1s[1].value);
}

// TODO(Xiaoyue Chen): Mock EntityManager and comprehensively test EntityView
struct EntityViewTest : public testing::Test {
  using TestComponentList = XnentList<C0, C1, C2>;
  using TestEntityView = EntityView<TestComponentList>;
  using ComponentTypeIDRegister =
      internal::XnentTypeIDRegister<TestComponentList>;
  using TestEntityManager = internal::EntityManager<2, 0>;
  using TestCompPool = internal::XnentPool<TestComponentList>;

  using TestPolicy = EnginePolicy<NeedList<TestComponentList, XnentList<>>>;
  using TestEngine = EinuEngine<TestPolicy>;

  EntityViewTest() {
    eid_pool = std::move(engine.CreateEIDPool());
    comp_pool = std::move(engine.CreateComponentPool());
    ett_mgr = std::move(engine.CreateEntityManager());
    ett_mgr->SetEIDPool(*eid_pool);
    ett_mgr->SetComponentPool(*comp_pool);
  }

  TestEngine engine;
  TestEntityManager mgr;
  TestEntityView view;
  std::unique_ptr<IEIDPool> eid_pool;
  std::unique_ptr<IXnentPool> comp_pool;
  std::unique_ptr<IEntityManager> ett_mgr;
};

TEST_F(EntityViewTest, _) {
  view.View(mgr);
  EXPECT_EQ(view.Components().begin(), view.Components().end());
  EXPECT_EQ(view.EIDs().begin(), view.EIDs().end());
}

TEST_F(EntityViewTest, __) {
  for (std::size_t i = 0; i != 10; ++i) {
    auto ett = ett_mgr->CreateEntity();
    auto& c0 = ett_mgr->AddComponent<C0>(ett);
    c0.value = 666;
    auto& c1 = ett_mgr->AddComponent<C1>(ett);
    c1.value = 123.4f;
  }

  {
    auto v = EntityView<XnentList<C0, C1>>();
    v.View(*ett_mgr);
    for (auto&& [c0, c1] : v.Components()) {
      EXPECT_EQ(c0.value, 666);
      EXPECT_FLOAT_EQ(c1.value, 123.4f);
    }
  }
  {
    auto v = EntityView<XnentList<C1, C0>>();
    v.View(*ett_mgr);
    for (auto&& [c1, c0] : v.Components()) {
      EXPECT_EQ(c0.value, 666);
      EXPECT_FLOAT_EQ(c1.value, 123.4f);
    }
  }
}

}  // namespace einu
