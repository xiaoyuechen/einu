#pragma once

#include "einu-engine/ai/behavior_tree/detail/single_node_owner.h"
#include "einu-engine/ai/behavior_tree/node.h"
#include "einu-engine/core/system.h"

namespace einu {
namespace ai {
namespace bt {

template <typename EntityManager, typename RequiredComponentList>
class Root : public System<EntityManager, RequiredComponentList>,
             public SingleNodeOwner {
 public:
  using System = System<EntityManager, RequiredComponentList>;

  using System::System;

  void Run(float dt) {
    System::RefreshMatchingBuffer();
    GetChild().Run(dt, System::GetMatchingBuffer().GetEntities());
  }
};

}  // namespace bt
}  // namespace ai
}  // namespace einu
