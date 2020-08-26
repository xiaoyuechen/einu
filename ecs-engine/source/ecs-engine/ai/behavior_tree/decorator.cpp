#include "ecs-engine/ai/behavior_tree/decorator.h"

namespace ecs {
namespace ai {
namespace bt {

const Result& Inverter::Run(float dt, const EntitySet& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  const auto& result = GetChild().Run(dt, etts);
  result_cache[Status::kRunning] = result[Status::kRunning];
  result_cache[Status::kSuccess] = result[Status::kFailure];
  result_cache[Status::kFailure] = result[Status::kSuccess];
  return result_cache;
}

const Result& Succeeder::Run(float dt, const EntitySet& etts) {
  Node::Run(dt, etts);
  GetChild().Run(dt, etts);
  GetResultCache()[Status::kSuccess] = etts;
  return GetResultCache();
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs