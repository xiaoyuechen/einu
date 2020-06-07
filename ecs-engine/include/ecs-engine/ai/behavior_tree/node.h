#pragma once

#include <vector>

#include "ecs-engine/ai/behavior_tree/result.h"

namespace ecs {
namespace ai {
namespace bt {

class Node {
 public:
  virtual ~Node() = default;

  virtual const Result& Run(float, const EntityDataVector&) {
    ClearResultCache();
    return GetResultCache();
  }

  Result& GetResultCache() noexcept { return result_cache_; }
  void ClearResultCache() noexcept { result_cache_.clear(); }

 private:
  mutable Result result_cache_;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
