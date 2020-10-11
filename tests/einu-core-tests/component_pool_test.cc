#include <einu-core/internal/component_pool.h>
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
  using ComponentPool = ComponentPool<ComponentList>;
  template <typename Comp>
  using ComponentPoolPolicy = ComponentPool::Policy<Comp>;
  template <typename Complist>
  struct PolicyTuple;
  template <typename... Comps>
  struct PolicyTuple<XnentList<Comps...>> {
    using Type = std::tuple<ComponentPoolPolicy<Comps>...>;
  };

  static constexpr std::size_t kCount =
      tmp::Size<ToTypeList<ComponentList>::Type>::value;
  ComponentPool pool;
  PolicyTuple<ComponentList>::Type policy_tuple{
      ComponentPoolPolicy<C0>{0},
      ComponentPoolPolicy<C1>{300, C1{}, [](auto size) { return size * 3; }},
      ComponentPoolPolicy<C2>{123},
      ComponentPoolPolicy<C3>{666},
  };
};

TEST_F(ComponentPoolTest, a_new_pool_is_empty) {
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}), 0);
  });
}

TEST_F(ComponentPoolTest, add_policy_will_grow_pool_size) {
  tmp::StaticFor<kCount>([&](auto i) {
    pool.AddPolicy(std::get<i>(policy_tuple), XnentTypeID{i});
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}),
              std::get<i>(policy_tuple).init_size);
  });
}

TEST_F(ComponentPoolTest,
       pool_size_would_grow_correctly_only_after_aquired_more_than_init_size) {
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    const auto& policy = std::get<ComponentPoolPolicy<Comp>>(policy_tuple);
    pool.AddPolicy(policy, XnentTypeID{i});

    auto init_size = policy.init_size;
    for (auto time = std::size_t{0}; time != init_size; ++time) {
      pool.Acquire<Comp>(XnentTypeID{i});
    }
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}), init_size);
    pool.Acquire<Comp>(XnentTypeID{i});
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}),
              init_size + policy.growth_func(init_size));
  });
}

TEST_F(ComponentPoolTest, acquire_release_aquire_would_not_make_pool_grow) {
  tmp::StaticFor<kCount>([&](auto i) {
    using Comp = tmp::TypeAt<ToTypeList<ComponentList>::Type, i>::Type;
    const auto& policy = std::get<ComponentPoolPolicy<Comp>>(policy_tuple);
    pool.AddPolicy(policy, XnentTypeID{i});

    auto acquired = std::vector<Comp*>{};
    auto init_size = policy.init_size;
    for (auto time = std::size_t{0}; time != init_size; ++time) {
      acquired.push_back(&pool.Acquire<Comp>(XnentTypeID{i}));
    }
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}), init_size);
    for (auto it = acquired.begin(); it != acquired.end(); ++it) {
      pool.Release<Comp>(*(*it), XnentTypeID{i});
    }
    EXPECT_EQ(pool.OnePoolSize<Comp>(XnentTypeID{i}), init_size);
  });
}

}  // namespace internal
}  // namespace einu