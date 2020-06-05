#pragma once

#include "ecs-engine/ai/behavior_tree/detail/single_node_owner.h"
#include "ecs-engine/ai/behavior_tree/node.h"
#include "ecs-engine/core/system.h"

namespace ecs {
namespace ai {
namespace bt {

template <typename EntityManager, typename RequiredComponentList>
class Root : public System<EntityManager, RequiredComponentList>,
             public SingleNodeOwner {
 public:
  using System = System<EntityManager, RequiredComponentList>;

  using System::System;
  void Run(float dt);
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager, typename RequiredComponentList>
void Root<EntityManager, RequiredComponentList>::Run(float dt) {
  System::GetMatchingComponentTuples();
  GetChild().Run(dt, System::GetEntityIDs());
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
