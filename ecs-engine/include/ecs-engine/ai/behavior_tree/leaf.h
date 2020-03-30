#pragma once

#include <algorithm>

#include "ecs-engine/ai/behavior_tree/node.h"
#include "ecs-engine/core/system.h"

namespace ecs {
namespace ai {
namespace bt {

template <typename EntityManager, typename RequiredComponentList>
class Leaf : public Node, public System<EntityManager, RequiredComponentList> {
 public:
  using System = System<EntityManager, RequiredComponentList>;
  using ComponentTupleBuffer = typename System::ComponentTupleBuffer;
  using EIDs = Node::EIDs;
  using ComponentTuple = typename System::ComponentTuple;

  Leaf(EntityManager& ett_mgr);
  virtual ~Leaf() = default;

  virtual const Result& Run(float dt, const EIDs& eids) override;

  const ComponentTupleBuffer& GetRelevantComponentTuples(const EIDs& eids);
  EntityID GetRelevantEntityID(const ComponentTuple& tup,
                               const EIDs& eids) const;

 private:
  ComponentTupleBuffer relevant_comps_;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager, typename RequiredComponentList>
inline Leaf<EntityManager, RequiredComponentList>::Leaf(EntityManager& ett_mgr)
    : System(ett_mgr) {}

template <typename EntityManager, typename RequiredComponentList>
inline const Result& Leaf<EntityManager, RequiredComponentList>::Run(
    float dt, const EIDs& eids) {
  const auto& result = Node::Run(dt, eids);
  System::GetMatchingComponentTuples();
  return result;
}

template <typename EntityManager, typename RequiredComponentList>
inline const typename Leaf<EntityManager,
                           RequiredComponentList>::ComponentTupleBuffer&
Leaf<EntityManager, RequiredComponentList>::GetRelevantComponentTuples(
    const EIDs& eids) {
  relevant_comps_.clear();
  const auto& all_eids = System::GetEntityIDs();
  auto it = all_eids.begin();
  for (const auto& eid : eids) {
    it = std::find(all_eids.begin(), all_eids.end(), eid);
    auto index = it - all_eids.begin();
    auto comp_tup = System::GetMatchingComponentTuples()[index];
    relevant_comps_.emplace_back(comp_tup);
  }
  return relevant_comps_;
}

template <typename EntityManager, typename RequiredComponentList>
inline EntityID Leaf<EntityManager, RequiredComponentList>::GetRelevantEntityID(
    const ComponentTuple& tup, const EIDs& eids) const {
  auto index = &tup - relevant_comps_.data();
  return eids[index];
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs