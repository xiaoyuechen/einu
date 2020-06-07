#include "pch.h"
// pre-compiled header

#include <ecs-engine/utility/iterator/filter.h>
#include <ecs-engine/utility/iterator/zip.h>

#include <typeinfo>

namespace ecs {

TEST(Filter, ANY) {
  auto v1 = std::vector<int>({1, 2, 3, 4});
  auto v2 = std::vector<float>({1.3f, 2.6f, 3.8f, 6.6f});
  auto vf = std::vector<int>{{1, 3, 4}};

  auto f = Filter(vf, v1, v2);
  EXPECT_EQ(*f.begin(), 1.3f);
  EXPECT_EQ(*(++f.begin()), 3.8f);
}

TEST(Zip, ANY) {
  const auto v1 = std::vector<int>({1, 2, 3, 4});
  const auto v2 = std::vector<float>({1.3f, 2.6f, 3.8f, 6.6f});
  auto z = Zip(v1, v2);
  EXPECT_EQ(*z.begin(), std::make_tuple(1, 1.3f));
}

TEST(CopyFilter, ANY) {
  auto v1 = std::vector<int>({1, 2, 3, 4});
  auto v2 = std::vector<float>({1.3f, 2.6f, 3.8f, 6.6f});
  auto vf = std::vector<int>{{3, 4}};
  auto f = CopyFilter(vf, v1, Zip(v2, v1));
  EXPECT_EQ(*f.begin(), std::make_tuple(3.8f, 3));
}

}  // namespace ecs
