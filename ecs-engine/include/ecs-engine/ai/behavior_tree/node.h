#pragma once

#include <vector>

#include "ecs-engine/ai/behavior_tree/result.h"

namespace ecs {
namespace ai {
namespace bt {

class Node {
 public:
  using EIDs = std::vector<EntityID>;

  virtual ~Node() = default;

  virtual const Result& Run(float dt, const EIDs& eids);

  Result& GetResultCache() noexcept;
  void ClearResultCache() noexcept;

 private:
  mutable Result result_cache_;
};

//////////////////////////////////////////////////////////////////////////

inline const Result& Node::Run(float, const EIDs&) {
  ClearResultCache();
  return GetResultCache();
}

inline Result& Node::GetResultCache() noexcept { return result_cache_; }

inline void Node::ClearResultCache() noexcept { result_cache_.clear(); }

}  // namespace bt
}  // namespace ai
}  // namespace ecs
