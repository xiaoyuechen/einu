#pragma once

#include <memory>

#include "ecs-engine/ai/behavior_tree/internal/single_node_owner.h"
#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class Decorator : public Node, public SingleNodeOwner {};

class Inverter : public Decorator {
 public:
  virtual const Result& Run(float dt, const EIDs& eids) override;
};

class Succeeder : public Decorator {
 public:
  virtual const Result& Run(float dt, const EIDs& eids) override;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
