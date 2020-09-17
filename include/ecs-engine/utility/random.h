#ifndef ECS_RANDOM_H_
#define ECS_RANDOM_H_

#include <random>

namespace ecs {

template <typename T>
T GetRandomInRange(const T min, const T max);

//////////////////////////////////////////////////////////////////////////

namespace component_manager_policy_internal {

inline std::random_device& GetRandomDevice() {
  static std::random_device device{};
  return device;
}

inline std::mt19937& GetGenerator() {
  static std::random_device device{};
  static std::mt19937 generator{GetRandomDevice()()};
  return generator;
}

}  // namespace component_manager_policy_internal

template <typename T>
inline T GetRandomInRange(const T min, const T max) {
  std::uniform_real_distribution<T> distribution(min, max);
  return distribution(component_manager_policy_internal::GetGenerator());
}

}  // namespace ecs

#endif  // RANDOM_H_