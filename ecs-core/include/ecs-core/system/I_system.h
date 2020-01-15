#pragma once
#include "ecs-core/component/Component_mask.h"

namespace ecs {
class I_system {
 public:
  const Component_mask& get_component_mask() const;
  virtual ~I_system() = 0;

 private:
  Component_mask component_mask;
};
}  // namespace ecs

namespace ecs {
inline const Component_mask& I_system::get_component_mask() const {
  return component_mask;
}

inline I_system::~I_system() {}
}  // namespace ecs