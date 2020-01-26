#ifndef COMPONENT_MASK_H_
#define COMPONENT_MASK_H_

#include "component_type_index.h"
#include "ecs-core/type_mask.h"

namespace ecs {

class ComponentMask : public TypeMask {
 public:
  ComponentMask() = default;
  ComponentMask(std::initializer_list<ComponentTypeIndex> il);

  ComponentMask& operator&=(const ComponentMask& rhs);
  ComponentMask& operator|=(const ComponentMask& rhs);

  void Insert(const ComponentTypeIndex& component_type_index);
  void Remove(const ComponentTypeIndex& component_type_index);

  bool HasType(const ComponentTypeIndex& component_type_index) const;
};

}  // namespace ecs
#endif  // COMPONENT_MASK_H_
