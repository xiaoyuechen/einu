#include "pch.h"
#include "ecs-core/object-pool/fixed_size_pool.h"
#include "ecs-core/utility/algorithm.h"
namespace ecs {

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
  FixedSizePool<Noncopyable> pool(10);
  EXPECT_EQ(pool.Size(), 10);
  EXPECT_EQ(pool.FreeSize(), 10);
}

TEST(FixedPool, ArgConstructor)
{
  FixedSizePool<Noncopyable> pool(10, std::forward_as_tuple(69));
  EXPECT_EQ(pool.Size(), 10);
  EXPECT_EQ(pool.FreeSize(), 10);
}

TEST(FixedPool, CopyConstructor)
{
  FixedSizePool<Copyable> pool(10, Copyable());
  EXPECT_EQ(pool.Size(), 10);
  EXPECT_EQ(pool.FreeSize(), 10);
}

TEST(FixedPool, Aquire)
{
  constexpr std::size_t size = 999;
  constexpr std::size_t aquire_size = 99;
  FixedSizePool<Noncopyable> pool(size, std::forward_as_tuple(69));
  algo::repeat(aquire_size, [&] {
    auto& obj = pool.Acquire();
    EXPECT_EQ(obj.data, 69); });
  EXPECT_EQ(pool.FreeSize(), size - aquire_size);
}

TEST(FixedPool, Recall)
{
  constexpr std::size_t size = 999;
  constexpr std::size_t aquire_size = 999;
  FixedSizePool<Noncopyable> pool(size, std::forward_as_tuple(69));

  auto aquired_obj_arr = std::vector<Noncopyable*>{};
  algo::repeat(aquire_size, [&] {
    auto& obj = pool.Acquire();
    aquired_obj_arr.push_back(&obj);
    EXPECT_EQ(obj.data, 69); });

  EXPECT_EQ(pool.FreeSize(), size - aquire_size);

  std::for_each(std::begin(aquired_obj_arr), std::end(aquired_obj_arr), [&](auto&& obj) {pool.Recall(*obj); });
  EXPECT_EQ(pool.FreeSize(), size);
}
}