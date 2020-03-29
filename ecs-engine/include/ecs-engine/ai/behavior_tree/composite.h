#pragma once

#include <memory>
#include <vector>

#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class Composite : public Node {
 public:
  void AddChild(std::unique_ptr<Node> child);
  const std::vector<std::unique_ptr<Node>>& GetChildren();

 private:
  std::vector<std::unique_ptr<Node>> children_;
};

class Sequence : public Composite {
 public:
  virtual Status Run(float dt) override;
};

class Selector : public Composite {
 public:
  virtual Status Run(float dt) override;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
