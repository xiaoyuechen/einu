#pragma once

#include "einu-engine/ai/behavior_tree/detail/multi_node_owner.h"
#include "einu-engine/ai/behavior_tree/node.h"

namespace einu {
namespace ai {
namespace bt {

class Composite : public Node, public MultiNodeOwner {};

class Sequence : public Composite {
 public:
  virtual const Result& Run(float dt, const EntitySet& etts) override;
};

class Selector : public Composite {
 public:
  virtual const Result& Run(float dt, const EntitySet& etts) override;
};

//////////////////////////////////////////////////////////////////////////

}  // namespace bt
}  // namespace ai
}  // namespace einu
