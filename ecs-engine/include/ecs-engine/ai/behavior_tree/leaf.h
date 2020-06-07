#pragma once

#include <algorithm>

#include "ecs-engine/ai/behavior_tree/node.h"
#include "ecs-engine/core/system.h"
#include "ecs-engine/utility/iterator/filter.h"
#include "ecs-engine/utility/iterator/zip.h"

namespace ecs {
namespace ai {
namespace bt {

template <typename EntityManager, typename RequiredComponentList>
class Leaf : public Node, public System<EntityManager, RequiredComponentList> {
 public:
  using System = System<EntityManager, RequiredComponentList>;

  Leaf(EntityManager& ett_mgr)
      : System(ett_mgr) {}
  virtual ~Leaf() = default;

  virtual const Result& Run(float dt, const EntityDataVector& etts) override {
    System::RefreshMatchingBuffer();
    return Node::Run(dt, etts);
  }

  auto FilterMatchingBuffer(const EntityDataVector& etts) const {
    const auto& matching_buffer = System::GetMatchingBuffer();
    return CopyFilter(
        etts, matching_buffer.GetEntities(),
        Zip(matching_buffer.GetComponents(), matching_buffer.GetEntities()));
  }
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs