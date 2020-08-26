#pragma once

#include "ecs-engine/core/entity.h"
#include "ecs-engine/core/entity_manager.h"
#include "ecs-engine/core/i_component.h"

namespace ecs {
namespace comp {

template <typename EntityManager>
struct EntityStorage : public IComponent {
  IEntity* ett;
  EntityManager* ett_mgr;
};

}  // namespace comp
}  // namespace ecs