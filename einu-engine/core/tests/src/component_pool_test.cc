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

#include <tuple>
#include <vector>

#include "einu-engine/core/internal/xnent_pool.h"
#include "gtest/gtest.h"
#include "src/xnents.h"
#include "tplusplus/static_algo.h"
#include "tplusplus/type_list.h"

namespace einu {
namespace internal {

struct ComponentPoolTest : public testing::Test {
  using ComponentList = XnentList<C0, C1, C2, C3>;
  using ComponentPool = XnentPool<ComponentList>;
  template <typename Comp>
  using ComponentPoolPolicy = ComponentPool::Policy<Comp>;
  template <typename Complist>
  struct PolicyTuple;
  template <typename... Xnents>
  struct PolicyTuple<XnentList<Xnents...>> {
    using Type = std::tuple<ComponentPoolPolicy<Xnents>...>;
  };

  static constexpr std::size_t kCount =
      tpp::Size<ToTypeList<ComponentList>::Type>::value;
  ComponentPool pool;
  PolicyTuple<ComponentList>::Type policy_tuple{
      ComponentPoolPolicy<C0>{0},
      ComponentPoolPolicy<C1>{300, std::make_unique<C1>(),
                              [](auto size) { return size * 3; }},
      ComponentPoolPolicy<C2>{123},
      ComponentPoolPolicy<C3>{666},
  };
};

TEST_F(ComponentPoolTest, a_new_pool_is_empty) {
  tpp::static_for<0, kCount>([&](auto i) {
    using Comp =
        typename tpp::TypeAt<typename ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}), 0);
  });
}

TEST_F(ComponentPoolTest, add_policy_will_grow_pool_size) {
  tpp::static_for<0, kCount>([&](auto i) {
    pool.AddPolicy(std::move(std::get<i>(policy_tuple)), XnentTypeID{i});
    using Comp =
        typename tpp::TypeAt<typename ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}),
              std::get<i>(policy_tuple).init_size);
  });
}

TEST_F(ComponentPoolTest,
       pool_size_would_grow_correctly_only_after_aquired_more_than_init_size) {
  tpp::static_for<0, kCount>([&](auto i) {
    using Comp =
        typename tpp::TypeAt<typename ToTypeList<ComponentList>::Type, i>::Type;
    auto&& policy = std::get<ComponentPoolPolicy<Comp>>(policy_tuple);
    pool.AddPolicy(std::move(policy), XnentTypeID{i});

    auto init_size = policy.init_size;
    for (auto time = std::size_t{0}; time != init_size; ++time) {
      pool.Acquire(XnentTypeID{i});
    }
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}), init_size);
    pool.Acquire(XnentTypeID{i});
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}),
              init_size + policy.growth_func(init_size));
  });
}

TEST_F(ComponentPoolTest, acquire_release_aquire_would_not_make_pool_grow) {
  tpp::static_for<0, kCount>([&](auto i) {
    using Comp =
        typename tpp::TypeAt<typename ToTypeList<ComponentList>::Type, i>::Type;
    auto&& policy = std::get<ComponentPoolPolicy<Comp>>(policy_tuple);
    pool.AddPolicy(std::move(policy), XnentTypeID{i});

    auto acquired = std::vector<Xnent*>{};
    auto init_size = policy.init_size;
    for (auto time = std::size_t{0}; time != init_size; ++time) {
      acquired.push_back(&pool.Acquire(XnentTypeID{i}));
    }
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}), init_size);
    for (auto it = acquired.begin(); it != acquired.end(); ++it) {
      pool.Release(XnentTypeID{i}, *(*it));
    }
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}), init_size);
  });
}

}  // namespace internal
}  // namespace einu
