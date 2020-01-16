#pragma once
#include "ecs-core/entity/Entity_id.h"

namespace ecs {
class I_component_manager {
 public:
  virtual ~I_component_manager() = 0;
  virtual void remove_component(const Entity_id& entity) = 0;
};
}

namespace ecs {
inline I_component_manager::~I_component_manager() {}
}