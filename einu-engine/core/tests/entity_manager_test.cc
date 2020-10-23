#include <einu-engine/core/internal/entity_manager.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

struct EntityManagerTest : public testing::Test {
  static constexpr std::size_t kMaxComponent = 256;
  static constexpr std::size_t kMaxSinglenent = 256;
  using EttMgr = EntityManager<kMaxComponent, kMaxSinglenent>;
  EttMgr ett_mgr;
};

TEST_F(EntityManagerTest, _) {}

}  // namespace internal
}  // namespace einu