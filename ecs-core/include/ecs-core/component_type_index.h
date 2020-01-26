#ifndef COMPONENT_TYPE_INDEX_H_
#define COMPONENT_TYPE_INDEX_H_

#include <type_traits>
#include <typeindex>

#include "ecs-core/i_component.h"

namespace ecs {

struct ComponentTypeIndex {
  std::type_index type_index;
};

template <typename T>
ComponentTypeIndex GetComponentTypeIndex();

//////////////////////////////////////////////////////////////////////////

template <typename T>
ComponentTypeIndex GetComponentTypeIndex() {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "T must inherit Component");
  return ComponentTypeIndex{std::type_index(typeid(T))};
}

}  // namespace ecs
#endif  // COMPONENT_TYPE_INDEX_H_
