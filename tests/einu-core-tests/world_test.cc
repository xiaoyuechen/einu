#include <einu-core/internal/world.h>
#include <gtest/gtest.h>

#include "mock_entity.h"

namespace einu {
namespace internal {

struct WorldTest : public testing::Test {
  MockEntity singlentity = MockEntity();
  World world;
  MockEntity ett;
  EntityBuffer buffer;
};

TEST_F(WorldTest, a_new_world_has_no_entity) {
  EXPECT_EQ(world.GetEntityCount(), 0);
  world.GetAllEntities(buffer);
  EXPECT_EQ(buffer.size(), 0);
}

TEST_F(WorldTest, can_get_entity_after_add) {
  world.AddEntity(ett);
  auto& r = world.GetEntity(ett.GetID());
  EXPECT_EQ(&ett, &r);
}

TEST_F(WorldTest, can_get_singlentity) {
  world.Singlentity() = singlentity;
  auto& r = world.GetSinglenity();
  EXPECT_EQ(&r, &singlentity);
}

}  // namespace internal
}  // namespace einu