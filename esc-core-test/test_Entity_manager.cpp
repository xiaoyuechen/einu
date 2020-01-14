#include "pch.h"
#include "ecs-core/managers/Entity_manager.h"
#include "ecs-core/utilities/algorithm.h"
#include <vector>
#include <thread>
#include <mutex>

TEST(EntityManager, SigleThread)
{
  using namespace ecs;
  auto m = Entity_manager{};
  auto e_arr = std::vector<Entity>{};
  algo::repeat(10, [&] {e_arr.push_back(m.create_entity()); });

  auto counter = std::size_t(0);
  std::for_each(std::begin(e_arr), std::end(e_arr),
                [&](auto&& e) {EXPECT_EQ(e.id(), counter++); });
}

TEST(EntityManager, MultiThread)
{
  using namespace ecs;
  auto m = Entity_manager{};
  auto e_arr = std::vector<Entity>{};
  e_arr.resize(10, Entity(0));

  auto ready = std::atomic<bool>(false);
  auto fn = [&](std::size_t count) { 
    while (!ready) { std::this_thread::yield(); }
    for (volatile int i = 0; i < 1000000; ++i) {}
    printf("thread %llu finished counting\n", count);
    auto e = m.create_entity();
    printf("thread %llu created entity %llu\n", count, e.id());
    e_arr[count] = e;
  };

  auto th_arr = std::vector<std::thread>{};
  for (auto i = size_t{}; i != 10; ++i) {
    th_arr.emplace_back(fn, i);
  }
  ready = true;

  std::for_each(std::begin(th_arr), std::end(th_arr),
                [](auto&& th) { th.join(); });

  for (auto i = std::size_t{}; i != 10; ++i) {
    auto found = std::find(std::begin(e_arr), std::end(e_arr), Entity(i));
    EXPECT_EQ(found == std::end(e_arr), false);
  }
}