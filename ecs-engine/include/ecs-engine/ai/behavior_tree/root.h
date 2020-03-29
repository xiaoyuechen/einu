#pragma once

#include <memory>
#include <vector>

#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class Root {
 public:
  void Run(float dt);
  void SetChild(std::unique_ptr<Node> child) noexcept;

 private:
  std::unique_ptr<Node> child_;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
