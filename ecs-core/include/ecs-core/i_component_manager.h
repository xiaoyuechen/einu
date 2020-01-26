#ifndef I_COMPONENT_MANAGER_H_
#define I_COMPONENT_MANAGER_H_

#include "ecs-core/entity_id.h"

namespace ecs {

class IComponentManager {
 public:
  virtual ~IComponentManager() = 0;
  virtual void RemoveComponent(const EntityID& entity) = 0;
};

//////////////////////////////////////////////////////////////////////////

inline IComponentManager::~IComponentManager() {}

}  // namespace ecs

#endif  // I_COMPONENT_MANAGER_H_