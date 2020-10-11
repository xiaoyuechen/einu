#include <einu-core/internal/entity_pool.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

struct EntityPoolTest : public testing::Test {
  static constexpr std::size_t kMaxComp = 22;
  using EntityPool = EntityPool<kMaxComp, SimpleEIDManager>;
  using Policy = EntityPool::Policy;

  SimpleEIDManager mgr;
  EntityPool pool{mgr};
  Policy plc{666};
};

TEST_F(EntityPoolTest, a_new_pool_is_empty) { EXPECT_EQ(pool.Size(), 0); }

bool InGoodState(const IEntity& ett) noexcept {
  if (ett.GetID() == ~EID{0}) return false;
  for (std::size_t i = 0; i != EntityPoolTest::kMaxComp; ++i) {
    if (ett.HasComponents(0, internal::DynamicXnentMask{XnentTypeID{i}}))
      return false;
  }
  return true;
}

TEST_F(EntityPoolTest, an_acquired_entity_is_in_good_state) {
  pool.SetPolicy(plc);
  for (std::size_t i = 0; i != 100; ++i) {
    auto& ett = pool.Acquire();
    EXPECT_TRUE(InGoodState(ett));
  }
}

TEST_F(EntityPoolTest, acquire_release_acquire_does_not_grow_the_pool) {
  using namespace std;
  pool.SetPolicy(plc);
  auto acquired = std::vector<IEntity*>(plc.init_size);
  for_each(acquired.begin(), acquired.end(),
           [&](auto& v) { v = &pool.Acquire(); });
  EXPECT_EQ(pool.Size(), plc.init_size);
  for_each(acquired.begin(), acquired.end(), [&](auto& v) {
    pool.Release(*v);
    v = nullptr;
  });
  EXPECT_EQ(pool.Size(), plc.init_size);
  for_each(acquired.begin(), acquired.end(),
           [&](auto& v) { v = &pool.Acquire(); });
  EXPECT_EQ(pool.Size(), plc.init_size);
}

}  // namespace internal
}  // namespace einu