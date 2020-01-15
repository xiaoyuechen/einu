#pragma once
#include <set>
#include "ecs-core/component/Component_type.h"

namespace ecs {
class Component_mask {
 public:
  using size_type = std::size_t;
  using init_list = std::initializer_list<Component_type>;

 private:
  using Mask = std::set<Component_type>;

 public:
  Component_mask() = default;
  explicit Component_mask(init_list l);

  void set(const Component_type& ct);
  void reset(const Component_type& ct);

  bool operator==(const Component_mask& rhs) const noexcept;
  bool operator!=(const Component_mask& rhs) const noexcept;
  Component_mask operator&(const Component_mask& rhs) const;
  Component_mask operator|(const Component_mask& rhs) const;
  Component_mask& operator&=(const Component_mask& rhs);
  Component_mask& operator|=(const Component_mask& rhs);

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