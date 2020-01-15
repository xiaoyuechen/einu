#include "ecs-core/component/Component_mask.h"
#include <algorithm>
#include <iterator>

namespace ecs {
Component_mask::Component_mask(Init_list l)
    : mask_(l) {
}

bool Component_mask::operator==(const Component_mask& rhs) const noexcept {
  return mask_ == rhs.mask_;
}

bool Component_mask::operator!=(const Component_mask& rhs) const noexcept {
  return !(*this == rhs);
}

Component_mask Component_mask::operator&(const Component_mask& rhs) const {
  auto result = Mask{};
   std::set_intersection(std::begin(mask_),
                        std::end(mask_),
                        std::begin(rhs.mask_),
                        std::end(rhs.mask_),
                        std::inserter(result, std::begin(result)));
  return Component_mask(result);
}

Component_mask Component_mask::operator|(const Component_mask& rhs) const {
  auto result = Mask{};
   std::set_union(std::begin(mask_),
                 std::end(mask_),
                 std::begin(rhs.mask_),
                 std::end(rhs.mask_),
                 std::inserter(result, std::begin(result)));
  return Component_mask(result);
}

}  // namespace ecs