#include "pch.h"
#include "ecs-core/object-pool/Fixed_pool.h"
#include "ecs-core/utilities/algorithm.h"

class Noncopyable {
public:
  Noncopyable() = default;
  Noncopyable(int i) { data = i; }
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable& operator=(const Noncopyable&) = delete;
  Noncopyable(Noncopyable&&) = default;
  int data = 0;
};

class Copyable {};

TEST(FixedPool, DefaultConstructor)
{
  ecs::Fixed_pool<Noncopyable> pool(10);
  EXPECT_EQ(pool.size(), 10);
  EXPECT_EQ(pool.free_size(), 10);
}

TEST(FixedPool, ArgConstructor)
{
  ecs::Fixed_pool<Noncopyable> pool(10, std::forward_as_tuple(69));
  EXPECT_EQ(pool.size(), 10);
  EXPECT_EQ(pool.free_size(), 10);
}

TEST(FixedPool, CopyConstructor)
{
  ecs::Fixed_pool<Copyable> pool(10, Copyable());
  EXPECT_EQ(pool.size(), 10);
  EXPECT_EQ(pool.free_size(), 10);
}

TEST(FixedPool, Aquire)
{
  constexpr std::size_t size = 999;
  constexpr std::size_t aquire_size = 99;
  ecs::Fixed_pool<Noncopyable> pool(size, std::forward_as_tuple(69));
  ecs::algo::repeat(aquire_size, [&] {
    auto obj = pool.aquire();
    EXPECT_EQ(obj->data, 69); });
  EXPECT_EQ(pool.free_size(), size - aquire_size);
}

TEST(FixedPool, Recall)
{
  constexpr std::size_t size = 999;
  constexpr std::size_t aquire_size = 999;
  ecs::Fixed_pool<Noncopyable> pool(size, std::forward_as_tuple(69));

  auto aquired_obj_arr = std::vector<Noncopyable*>{};
  ecs::algo::repeat(aquire_size, [&] {
    auto obj = pool.aquire();
    aquired_obj_arr.push_back(obj);
    EXPECT_EQ(obj->data, 69); });

  EXPECT_EQ(pool.free_size(), size - aquire_size);

  std::for_each(std::begin(aquired_obj_arr), std::end(aquired_obj_arr), [&](auto&& obj) {pool.recall(obj); });
  EXPECT_EQ(pool.free_size(), size);
}