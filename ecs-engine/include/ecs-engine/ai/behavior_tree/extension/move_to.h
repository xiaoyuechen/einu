#pragma once

#include "ecs-engine/ai/behavior_tree/extension/destination_component.h"
#include "ecs-engine/ai/behavior_tree/leaf.h"
#include "ecs-engine/extension/component/movement_component.h"
#include "ecs-engine/extension/component/transform_component.h"

namespace ecs {
namespace ai {
namespace bt {

using MoveToRequiredComponentList =
    ComponentList<const TransformComponent, MovementComponent,
                  const DestinationComponent>;

template <typename EntityManager>
class MoveTo : public Leaf<EntityManager, MoveToRequiredComponentList> {
  using Leaf = Leaf<EntityManager, MoveToRequiredComponentList>;

 public:
  MoveTo(EntityManager& ett_mgr);
  virtual const Result& Run(float dt, const typename Leaf::EIDs& eids) override;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager>
inline MoveTo<EntityManager>::MoveTo(EntityManager& ett_mgr)
    : Leaf(ett_mgr) {}

template <typename EntityManager>
inline const Result& MoveTo<EntityManager>::Run(
    float dt, const typename Leaf::EIDs& eids) {
  Leaf::Run(dt, eids);
  auto& result = Leaf::GetResultCache();
  for (const auto& tup : Leaf::GetRelevantComponentTuples(eids)) {
    auto eid = Leaf::GetRelevantEntityID(tup, eids);
    auto& [transform_comp, movement_comp, dest_comp] = tup;
    auto delta = dest_comp.destination - transform_comp.transform.GetPosition();
    if (glm::length2(delta) < glm::pow(dest_comp.tolerance_radius, 2)) {
      movement_comp.direction = glm::vec3();
      result[Status::SUCCESS].emplace_back(eid);
    } else {
      movement_comp.direction = glm::normalize(delta);
      movement_comp.speed = movement_comp.max_speed;
      result[Status::RUNNING].emplace_back(eid);
    }
  }
  return result;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs