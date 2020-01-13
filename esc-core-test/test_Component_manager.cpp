#include "pch.h"
#include "ecs-core/managers/Component_manager.h"

struct Comp {
  float x, y, z;
};

TEST(ComponentManager, Add){
  using namespace ecs;
  auto pool = Fixed_pool<Comp>(969);
  auto manager = Component_manager(pool);
  manager.add(Entity(0));
}

TEST(ComponentManager, Get)
{
  using namespace ecs;
  auto pool = Fixed_pool<Comp>(969);
  auto manager = Component_manager(pool);
  auto e = Entity(0);
  manager.add(e);
  auto comp = manager.get(e);
  EXPECT_EQ(pool.free_size(), 968);
}

TEST(ComponentManager, Remove)
{
  using namespace ecs;
  auto pool = Fixed_pool<Comp>(969);
  auto manager = Component_manager(pool);
  auto e = Entity(0);
  manager.add(e);
  auto comp = manager.get(e);
  EXPECT_EQ(pool.free_size(), 968);
  manager.remove(e);
  EXPECT_EQ(pool.free_size(), 969);
}

TEST(ComponentManager, HandleDestroy)
{
  using namespace ecs;
  auto pool = Fixed_pool<Comp>(969);
  auto manager = Component_manager(pool);
  auto e = Entity(0);
  manager.add(e);
  auto comp = manager.get(e);
  EXPECT_EQ(pool.free_size(), 968);
  comp.destroy();
  EXPECT_EQ(pool.free_size(), 969);
}