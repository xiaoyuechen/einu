#pragma once

#include <memory>

#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class SingleNodeOwner {
 public:
  template <typename T, typename... Args>
  T& SetChild(Args&&... args) noexcept;

  Node& GetChild() noexcept;
  const Node& GetChild() const noexcept;

 private:
  std::unique_ptr<Node> child_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
T& SingleNodeOwner::SetChild(Args&&... args) noexcept {
  child_ = std::make_unique<T>(std::forward<Args>(args)...);
  return static_cast<T&>(*child_);
}

inline Node& ecs::ai::bt::SingleNodeOwner::GetChild() noexcept {
  return *child_;
}

inline const Node& SingleNodeOwner::GetChild() const noexcept {
  return *child_;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs