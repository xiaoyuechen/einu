#include "ecs-engine/ai/behavior_tree/decorator.h"

namespace ecs {
namespace ai {
namespace bt {

void Decorator::SetChild(std::unique_ptr<Node> child) noexcept {
  child_ = std::move(child);
}

Status Inverter::Run(float dt) {
  auto status = child_->Run(dt);
  switch (status) {
    case ecs::ai::bt::Status::SUCCESS:
      return Status::FAILURE;
    case ecs::ai::bt::Status::FAILURE:
      return Status::SUCCESS;
  }
  return status;
}

Status Succeeder::Run(float dt) {
  auto status = child_->Run(dt);
  if (status == Status::FAILURE) {
    return Status::SUCCESS;
  }
  return status;
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs