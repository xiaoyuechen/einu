#include "ecs-engine/ai/behavior_tree/decorator.h"

namespace ecs {
namespace ai {
namespace bt {

const Result& Inverter::Run(float dt, const EntityDataVector& etts) {
  Node::Run(dt, etts);
  auto& result_cache = GetResultCache();
  const auto& result = GetChild().Run(dt, etts);
  result_cache[Status::RUNNING] = result[Status::RUNNING];
  result_cache[Status::SUCCESS] = result[Status::FAILURE];
  result_cache[Status::FAILURE] = result[Status::SUCCESS];
  return result_cache;
}

const Result& Succeeder::Run(float dt, const EntityDataVector& etts) {
  Node::Run(dt, etts);
  GetChild().Run(dt, etts);
  GetResultCache()[Status::SUCCESS] = etts;
  return GetResultCache();
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs