#pragma once
#include <set>
#include "ecs-core/component/Component_type.h"

namespace ecs {
class Component_mask {
 public:
  using size_type = std::size_t;
  using Init_list = std::initializer_list<Component_type>;

 private:
  using Mask = std::set<Component_type>;

 public:
  Component_mask() = default;
  explicit Component_mask(Init_list l);

  bool operator==(const Component_mask& rhs) const noexcept;
  bool operator!=(const Component_mask& rhs) const noexcept;
  Component_mask operator&(const Component_mask& rhs) const;
  Component_mask operator|(const Component_mask& rhs) const;

 private:
  Component_mask(const Mask& mask);

 private:
  Mask mask_;
};
}  // namespace ecs

namespace ecs {
inline Component_mask::Component_mask(const Mask& mask)
    : mask_(mask) {}
}  // namespace ecs