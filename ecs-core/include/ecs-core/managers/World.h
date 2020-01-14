#pragma once
#include "ecs-core/managers/Component_manager.h"
#include "ecs-core/managers/Entity_manager.h"

namespace ecs {
class World {
 public:

 private:
  Entity_manager entity_manager_;
};
}  // namespace ecs