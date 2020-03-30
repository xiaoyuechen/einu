#include "ecs-engine/ai/behavior_tree/composite.h"

namespace ecs {
namespace ai {
namespace bt {

void Composite::AddChild(std::unique_ptr<Node> child) {
  children_.emplace_back(std::move(child));
}

const std::vector<std::unique_ptr<Node>>& Composite::GetChildren() {
  return children_;
}

const Result& Sequence::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  auto& result_cache = GetResultCache();
  result_cache[Status::SUCCESS] = eids;
  for (auto&& child : GetChildren()) {
    result_cache = child->Run(dt, result_cache[Status::SUCCESS]);
  }
  return result_cache;
}

const Result& Selector::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  auto& result_cache = GetResultCache();
  result_cache[Status::FAILURE] = eids;
  for (auto&& child : GetChildren()) {
    result_cache = child->Run(dt, result_cache[Status::FAILURE]);
  }
  return result_cache;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
