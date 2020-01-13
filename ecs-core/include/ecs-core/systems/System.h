#pragma once
#include "ecs-core/components/Component_mask.h"

namespace ecs {
class System {
 public:
  const Component_mask& get_component_mask() const;
 protected:
  virtual ~System() = default;
 private:
  Component_mask component_mask;
};

inline const Component_mask& System::get_component_mask() const
{
  return component_mask;
}
}  // namespace ecs