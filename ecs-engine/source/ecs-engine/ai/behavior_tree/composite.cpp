#include "ecs-engine/ai/behavior_tree/composite.h"

namespace ecs {
namespace ai {
namespace bt {

const Result& Sequence::Run(float dt, const EntityDataVector& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  result_cache[Status::SUCCESS] = etts;
  for (auto&& child : GetChildren()) {
    auto& result = child->Run(dt, result_cache[Status::SUCCESS]);
    result_cache[Status::SUCCESS] = result[Status::SUCCESS];
    std::copy(result[Status::FAILURE].begin(), result[Status::FAILURE].end(),
              std::back_inserter(result_cache[Status::FAILURE]));
    std::copy(result[Status::RUNNING].begin(), result[Status::RUNNING].end(),
              std::back_inserter(result_cache[Status::RUNNING]));
  }
  return result_cache;
}

const Result& Selector::Run(float dt, const EntityDataVector& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  result_cache[Status::FAILURE] = etts;
  for (auto&& child : GetChildren()) {
    auto& result = child->Run(dt, result_cache[Status::FAILURE]);
    result_cache[Status::FAILURE] = result[Status::FAILURE];
    std::copy(result[Status::SUCCESS].begin(), result[Status::SUCCESS].end(),
              std::back_inserter(result_cache[Status::SUCCESS]));
    std::copy(result[Status::RUNNING].begin(), result[Status::RUNNING].end(),
              std::back_inserter(result_cache[Status::RUNNING]));
  }
  return result_cache;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
