#pragma once

#include "einu-engine/core/entity.h"
#include "einu-engine/core/entity_manager.h"
#include "einu-engine/core/i_component.h"

namespace einu {
namespace comp {

template <typename EntityManager>
struct EntityStorage : public IComponent {
  IEntity* ett;
  EntityManager* ett_mgr;
};

}  // namespace comp
}  // namespace einu