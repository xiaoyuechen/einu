#include "ecs-core/components/Component_mask.h"
#include <algorithm>

namespace ecs {
Component_mask::Component_mask(Init_list l) {
  std::for_each(
      std::begin(l), std::end(l), [&](auto&& t) { mask_.set(t.id()); });
}

bool Component_mask::operator==(const Component_mask& rhs) const noexcept {
  return mask_ == rhs.mask_;
}

bool Component_mask::operator!=(const Component_mask& rhs) const noexcept {
  return !(*this == rhs);
}

Component_mask Component_mask::operator&(const Component_mask& rhs) const
    noexcept {
  return Component_mask(mask_ & rhs.mask_);
}

Component_mask Component_mask::operator|(const Component_mask& rhs) const
    noexcept {
  return Component_mask(mask_ | rhs.mask_);
}

}  // namespace ecs