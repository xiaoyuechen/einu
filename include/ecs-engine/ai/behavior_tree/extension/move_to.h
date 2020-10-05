#pragma once

#include "einu-engine/ai/behavior_tree/extension/destination_component.h"
#include "einu-engine/ai/behavior_tree/leaf.h"
#include "einu-engine/extension/component/movement_component.h"
#include "einu-engine/extension/component/transform_component.h"

namespace einu {
namespace ai {
namespace bt {

using MoveToRequiredComponentList =
    ComponentList<const TransformComponent, MovementComponent,
                  const DestinationComponent>;

template <typename EntityManager>
class MoveTo : public Leaf<EntityManager, MoveToRequiredComponentList> {
  using Leaf = Leaf<EntityManager, MoveToRequiredComponentList>;

 public:
  MoveTo(EntityManager& ett_mgr)
      : Leaf(ett_mgr) {}

  virtual const Result& Run(float dt, const EntityDataVector& etts) override {
    Leaf::Run(dt, etts);
    auto& result = Leaf::GetResultCache();
    for (const auto& [comp, ett] : Leaf::FilterMatchingBuffer(etts)) {
      auto& [transform_comp, movement_comp, dest_comp] = comp;
      auto delta =
          dest_comp.destination - transform_comp.transform.GetPosition();
      if (glm::length2(delta) < glm::pow(dest_comp.tolerance_radius, 2)) {
        movement_comp.direction = glm::vec3();
        result[Status::kSuccess].emplace_back(ett);
      } else {
        movement_comp.direction = glm::normalize(delta);
        movement_comp.speed = movement_comp.max_speed;
        result[Status::kRunning].emplace_back(ett);
      }
    }
    return result;
  }
};

}  // namespace bt
}  // namespace ai
}  // namespace einu