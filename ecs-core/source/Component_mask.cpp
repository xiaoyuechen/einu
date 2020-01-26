#include "ecs-core/component_mask.h"

#include <algorithm>

namespace ecs {

ComponentMask::ComponentMask(std::initializer_list<ComponentTypeIndex> il) {
  for (auto it = il.begin(); it != il.end(); ++it) {
    Insert(*it);
  }
}

ComponentMask& ComponentMask::operator&=(const ComponentMask& rhs) {
  TypeMask::operator&=(rhs);
  return *this;
}

ComponentMask& ComponentMask::operator|=(const ComponentMask& rhs) {
  TypeMask::operator|=(rhs);
  return *this;
}

void ComponentMask::Insert(const ComponentTypeIndex& component_type_index) {
  TypeMask::Insert(component_type_index.type_index);
}

void ComponentMask::Remove(const ComponentTypeIndex& component_type_index) {
  TypeMask::Remove(component_type_index.type_index);
}

bool ComponentMask::HasType(
    const ComponentTypeIndex& component_type_index) const {
  return TypeMask::HasType(component_type_index.type_index);
}

}  // namespace ecs