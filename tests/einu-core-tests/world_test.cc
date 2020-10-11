#include <einu-core/internal/world.h>
#include <gtest/gtest.h>

#include "mock_entity.h"

namespace einu {
namespace internal {

struct WorldTest : public testing::Test {
  World world{std::make_unique<MockEntity>()};
};

TEST_F(WorldTest, a_new_world_has_no_entity) {
  EXPECT_EQ(world.GetEntityCount(), 0);
}

TEST_F(WorldTest, can_get_entity_after_add) {}

}  // namespace internal
}  // namespace einu