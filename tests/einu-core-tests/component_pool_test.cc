#include <einu-core/internal/xnent_pool.h>
#include <einu-tmp/static_algo.h>
#include <einu-tmp/type_list.h>
#include <gtest/gtest.h>

#include <tuple>
#include <vector>

#include "xnents.h"

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
      tmp::Size<ToTypeList<ComponentList>::Type>::value;
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
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}), 0);
  });
}

TEST_F(ComponentPoolTest, add_policy_will_grow_pool_size) {
  tmp::StaticFor<kCount>([&](auto i) {
    pool.AddPolicy(std::move(std::get<i>(policy_tuple)), XnentTypeID{i});
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize(XnentTypeID{i}),
              std::get<i>(policy_tuple).init_size);
  });
}

TEST_F(ComponentPoolTest,
       pool_size_would_grow_correctly_only_after_aquired_more_than_init_size) {
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
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
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
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