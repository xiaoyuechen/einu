#include "ecs-engine/ai/behavior_tree/root.h"

namespace ecs {
namespace ai {
namespace bt {

void Root::Run(float dt) { child_->Run(dt); }

void Root::SetChild(std::unique_ptr<Node> child) noexcept {
  child_ = std::move(child);
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs
