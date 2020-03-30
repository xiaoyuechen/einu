#pragma once

#include <memory>
#include <vector>

#include "ecs-engine/ai/behavior_tree/node.h"
#include "ecs-engine/core/system.h"

namespace ecs {
namespace ai {
namespace bt {

template <typename EntityManager, typename RequiredComponentList>
class Root : public System<EntityManager, RequiredComponentList> {
 public:
  using System::System;
  void Run(float dt);
  void SetChild(std::unique_ptr<Node> child) noexcept;

 private:
  std::unique_ptr<Node> child_;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager, typename RequiredComponentList>
void Root<EntityManager, RequiredComponentList>::Run(float dt) {
  child_->Run(dt, System::GetEntityIDs());
}

template <typename EntityManager, typename RequiredComponentList>
void Root<EntityManager, RequiredComponentList>::SetChild(
    std::unique_ptr<Node> child) noexcept {
  child_ = std::move(child);
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
