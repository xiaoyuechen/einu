#include "ecs-engine/ai/behavior_tree/composite.h"

namespace ecs {
namespace ai {
namespace bt {

void Composite::AddChild(std::unique_ptr<Node> child) {
  children_.emplace_back(std::move(child));
}

const std::vector<std::unique_ptr<Node>>& Composite::GetChildren() {
  return children_;
}

Status Sequence::Run(float dt) {
  for (auto&& child : GetChildren()) {
    auto status = child->Run(dt);
    if (status != Status::SUCCESS) {
      return status;
    }
  }
  return Status::SUCCESS;
}

Status Selector::Run(float dt) {
  for (auto&& child : GetChildren()) {
    auto status = child->Run(dt);
    if (status != Status::FAILURE) {
      return status;
    }
  }
  return Status::FAILURE;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
