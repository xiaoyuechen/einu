#include "einu-engine/ai/behavior_tree/composite.h"

namespace einu {
namespace ai {
namespace bt {

const Result& Sequence::Run(float dt, const EntitySet& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  result_cache[Status::kSuccess] = etts;
  for (auto&& child : GetChildren()) {
    auto& result = child->Run(dt, result_cache[Status::kSuccess]);
    result_cache[Status::kSuccess] = result[Status::kSuccess];
    std::copy(result[Status::kFailure].begin(), result[Status::kFailure].end(),
              std::back_inserter(result_cache[Status::kFailure]));
    std::copy(result[Status::kRunning].begin(), result[Status::kRunning].end(),
              std::back_inserter(result_cache[Status::kRunning]));
  }
  return result_cache;
}

const Result& Selector::Run(float dt, const EntitySet& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  result_cache[Status::kFailure] = etts;
  for (auto&& child : GetChildren()) {
    auto& result = child->Run(dt, result_cache[Status::kFailure]);
    result_cache[Status::kFailure] = result[Status::kFailure];
    std::copy(result[Status::kSuccess].begin(), result[Status::kSuccess].end(),
              std::back_inserter(result_cache[Status::kSuccess]));
    std::copy(result[Status::kRunning].begin(), result[Status::kRunning].end(),
              std::back_inserter(result_cache[Status::kRunning]));
  }
  return result_cache;
}

}  // namespace bt
}  // namespace ai
}  // namespace einu
