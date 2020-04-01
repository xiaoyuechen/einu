#pragma once

#include "ecs-engine/ai/behavior_tree/internal/multi_node_owner.h"
#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class Composite : public Node, public MultiNodeOwner {};

class Sequence : public Composite {
 public:
  virtual const Result& Run(float dt, const EIDs& eids) override;
};

class Selector : public Composite {
 public:
  virtual const Result& Run(float dt, const EIDs& eids) override;
};

//////////////////////////////////////////////////////////////////////////

}  // namespace bt
}  // namespace ai
}  // namespace ecs
