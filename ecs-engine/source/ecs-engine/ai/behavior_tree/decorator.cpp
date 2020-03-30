#include "ecs-engine/ai/behavior_tree/decorator.h"

namespace ecs {
namespace ai {
namespace bt {

void Decorator::SetChild(std::unique_ptr<Node> child) noexcept {
  child_ = std::move(child);
}

const Result& Inverter::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  auto& result_cache = GetResultCache();
  const auto& result = child_->Run(dt, eids);
  result_cache[Status::RUNNING] = result[Status::RUNNING];
  result_cache[Status::SUCCESS] = result[Status::FAILURE];
  result_cache[Status::FAILURE] = result[Status::SUCCESS];
  return result_cache;
}

const Result& Succeeder::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  auto& result_cache = GetResultCache();
  const auto& result = child_->Run(dt, eids);
  result_cache[Status::RUNNING] = result[Status::RUNNING];
  result_cache[Status::SUCCESS] = result[Status::SUCCESS];
  const auto& failure_eids = result[Status::FAILURE];
  std::copy(failure_eids.begin(), failure_eids.end(),
            std::back_inserter(result_cache[Status::SUCCESS]));
  return result_cache;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs