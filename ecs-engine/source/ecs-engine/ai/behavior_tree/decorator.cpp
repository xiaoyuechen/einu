#include "ecs-engine/ai/behavior_tree/decorator.h"

namespace ecs {
namespace ai {
namespace bt {

const Result& Inverter::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  auto& result_cache = GetResultCache();
  const auto& result = GetChild().Run(dt, eids);
  result_cache[Status::RUNNING] = result[Status::RUNNING];
  result_cache[Status::SUCCESS] = result[Status::FAILURE];
  result_cache[Status::FAILURE] = result[Status::SUCCESS];
  return result_cache;
}

const Result& Succeeder::Run(float dt, const EIDs& eids) {
  Node::Run(dt, eids);
  GetChild().Run(dt, eids);
  GetResultCache()[Status::SUCCESS] = eids;
  return GetResultCache();
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs