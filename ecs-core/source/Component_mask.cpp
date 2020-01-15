#include "ecs-core/component/Component_mask.h"
#include <algorithm>
#include <iterator>

namespace ecs {
Component_mask::Component_mask(init_list l)
    : mask_(l) {}

void Component_mask::set(const Component_type& ct) { mask_.insert(ct); }

void Component_mask::reset(const Component_type& ct) { mask_.erase(ct); }

typename Component_mask::iterator Component_mask::cbegin() {
  return std::cbegin(mask_);
}

typename Component_mask::iterator Component_mask::cend() {
  return std::cend(mask_);
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

Component_mask& Component_mask::operator&=(const Component_mask& rhs) {
  *this = *this & rhs;
  return *this;
}

Component_mask& Component_mask::operator|=(const Component_mask& rhs) {
  *this = *this | rhs;
  return *this;
}

}  // namespace ecs