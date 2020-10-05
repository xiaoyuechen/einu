#pragma once

#include <vector>

#include "einu-engine/ai/behavior_tree/result.h"

namespace einu {
namespace ai {
namespace bt {

class Node {
 public:
  using EntitySet = Result::EntitySet;

  virtual ~Node() = default;

  virtual const Result& Run(float, const EntitySet&) {
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
}  // namespace einu
