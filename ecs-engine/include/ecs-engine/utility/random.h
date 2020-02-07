#ifndef ECS_RANDOM_H_
#define ECS_RANDOM_H_

#include <random>

namespace ecs {

template <typename T>
T GetRandomInRange(const T min, const T max);

//////////////////////////////////////////////////////////////////////////

namespace detail {
std::random_device& GetRandomDevice() {
  static std::random_device device{};
  return device;
}

std::mt19937& GetGenerator() {
  static std::random_device device{};
  static std::mt19937 generator{GetRandomDevice()()};
  return generator;
}
}  // namespace detail

template <typename T>
T GetRandomInRange(const T min, const T max) {
  std::uniform_real_distribution<T> distribution(min, max);
  return distribution(detail::GetGenerator());
}

}  // namespace ecs

#endif  // RANDOM_H_