#ifndef COMPONENT_ARRAY_H_
#define COMPONENT_ARRAY_H_

#include <array>

#include "ecs-core/component_setting.h"
#include "ecs-core/component_tag.h"

namespace ecs {

template <typename ComponentSetting>
class ComponentArray {
 public:
  template <typename T>
  void Insert(T& component) noexcept;
  template <typename T>
  void Erase() noexcept;

  template <typename T>
  const T& Get() const noexcept;
  template <typename T>
  T& Get() noexcept;

 private:
  static constexpr auto kComponentTypeCount =
      ComponentSetting::GetComponentTypeCount();
  std::array<ComponentTag*, kComponentTypeCount> arr_{nullptr};
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentSetting>
template <typename T>
inline void ComponentArray<ComponentSetting>::Insert(T& component) noexcept {
  auto constexpr index = ComponentSetting::template GetComponentTypeIndex<T>();
  arr_[index] = &component;
}

template <typename ComponentSetting>
template <typename T>
inline void ComponentArray<ComponentSetting>::Erase() noexcept {
  constexpr auto index = ComponentSetting::template GetComponentTypeIndex<T>();
  arr_[index] = nullptr;
}

template <typename ComponentSetting>
template <typename T>
inline const T& ComponentArray<ComponentSetting>::Get() const noexcept {
  constexpr auto index = ComponentSetting::template GetComponentTypeIndex<T>();
  return reinterpret_cast<const T&>(*arr_[index]);
}

template <typename ComponentSetting>
template <typename T>
inline T& ComponentArray<ComponentSetting>::Get() noexcept {
  return const_cast<T&>(static_cast<const ComponentArray&>(*this).Get<T>());
}

}  // namespace ecs

#endif  // COMPONENT_ARRAY_H_