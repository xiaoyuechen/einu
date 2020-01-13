#pragma once
#include <tuple>
#include <unordered_map>
#include <vector>
#include "ecs-core/components/Component.h"
#include "ecs-core/entities/Entity.h"

namespace ecs {
class Entity_manager {
 public:

 private:
  std::unordered_map<Entity, std::vector<Component*>> entities;
};
}  // namespace ecs