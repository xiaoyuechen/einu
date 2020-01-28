#ifndef COMPONENT_SETTING_H_
#define COMPONENT_SETTING_H_

#include <bitset>

#include "ecs-core/utility/type_list.h"

namespace ecs {

template <typename... Ts>
using ComponentList = TypeList<Ts...>;

template <typename ComponentList>
struct ComponentSetting {
  static constexpr std::size_t GetComponentTypeCount();

  using ComponentMask = std::bitset<GetComponentTypeCount()>;
  using ComponentTypeIndex = std::size_t;

  template <typename T>
  static constexpr ComponentTypeIndex GetComponentTypeIndex();

  template <typename... Ts>
  static ComponentMask GetComponentMask();
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentList>
template <typename T>
inline constexpr typename ComponentSetting<ComponentList>::ComponentTypeIndex
ComponentSetting<ComponentList>::GetComponentTypeIndex() {
  return IndexOf<ComponentList, std::remove_const<T>::type>::value;
}

template <typename ComponentList>
template <typename... Ts>
typename ComponentSetting<ComponentList>::ComponentMask
ComponentSetting<ComponentList>::GetComponentMask() {
  ComponentMask mask;
  (mask.set(GetComponentTypeIndex<Ts>()), ...);
  return mask;
}

template <typename ComponentList>
inline constexpr std::size_t
ComponentSetting<ComponentList>::GetComponentTypeCount() {
  return Size<ComponentList>::value;
}

}  // namespace ecs

#endif  // COMPONENT_SETTING_H_