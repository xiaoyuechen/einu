#pragma once

#include <memory>

#include "ecs-engine/ai/behavior_tree/node.h"

namespace ecs {
namespace ai {
namespace bt {

class Decorator : public Node {
 public:
  void SetChild(std::unique_ptr<Node> child) noexcept;

 protected:
  std::unique_ptr<Node> child_;
};

class Inverter : public Decorator {
 public:
  virtual Status Run(float dt) override;
};

class Succeeder : public Decorator {
 public:
  virtual Status Run(float dt) override;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
