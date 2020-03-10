#ifndef COMPONENT_SETTING_H_
#define COMPONENT_SETTING_H_

#include <bitset>

#include "ecs-engine/utility/type_list.h"

namespace ecs {

template <typename... Ts>
using ComponentList = TypeList<Ts...>;

template <typename ComponentList, typename SingletonComponentList>
struct ComponentSetting {
  using Components = ComponentList;
  using SingletonComponents = SingletonComponentList;

  static constexpr std::size_t GetComponentTypeCount();

  using ComponentMask = std::bitset<GetComponentTypeCount()>;
  using ComponentTypeIndex = std::size_t;

  template <typename T>
  static constexpr ComponentTypeIndex GetComponentTypeIndex();

  template <typename... Ts>
  static ComponentMask GetComponentMask();

  template <ComponentTypeIndex index>
  using ComponentTypeAt = typename TypeAt<ComponentList, index>::Type;
};

//////////////////////////////////////////////////////////////////////////

template <typename ComponentList, typename SingletonComponentList>
inline constexpr std::size_t ComponentSetting<
    ComponentList, SingletonComponentList>::GetComponentTypeCount() {
  return Size<ComponentList>::value;
}

template <typename ComponentList, typename SingletonComponentList>
template <typename T>
inline constexpr
    typename ComponentSetting<ComponentList,
                              SingletonComponentList>::ComponentTypeIndex
    ComponentSetting<ComponentList,
                     SingletonComponentList>::GetComponentTypeIndex() {
  return IndexOf<ComponentList, std::remove_const<T>::type>::value;
}

template <typename ComponentList, typename SingletonComponentList>
template <typename... Ts>
typename ComponentSetting<ComponentList, SingletonComponentList>::ComponentMask
ComponentSetting<ComponentList, SingletonComponentList>::GetComponentMask() {
  ComponentMask mask;
  (mask.set(GetComponentTypeIndex<Ts>()), ...);
  return mask;
}

}  // namespace ecs

#endif  // COMPONENT_SETTING_H_