#pragma once

#include <memory>
#include <vector>

#include "einu-engine/ai/behavior_tree/node.h"

namespace einu {
namespace ai {
namespace bt {

class MultiNodeOwner {
 public:
  template <typename T, typename... Args>
  T& AddChild(Args&&... args);

  std::vector<std::unique_ptr<Node>>& GetChildren();
  const std::vector<std::unique_ptr<Node>>& GetChildren() const;

 private:
  std::vector<std::unique_ptr<Node>> children_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
inline T& MultiNodeOwner::AddChild(Args&&... args) {
  children_.push_back(
      std::move(std::make_unique<T>(std::forward<Args>(args)...)));
  return static_cast<T&>(*children_.back());
}

inline std::vector<std::unique_ptr<Node>>& MultiNodeOwner::GetChildren() {
  return children_;
}

inline const std::vector<std::unique_ptr<Node>>& MultiNodeOwner::GetChildren()
    const {
  return children_;
}

}  // namespace bt
}  // namespace ai
}  // namespace einu