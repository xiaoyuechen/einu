#pragma once

#include "ecs-engine/ai/behavior_tree/status.h"

namespace ecs {
namespace ai {
namespace bt {

class Node {
 public:
  virtual ~Node() = default;

  virtual Status Run(float dt) = 0;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs
