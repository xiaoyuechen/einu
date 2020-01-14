#pragma once
#include <bitset>
#include <initializer_list>
#include "ecs-core/components/Component_type.h"

namespace ecs {
class Component_mask {
 public:
  using size_type = std::size_t;
  using Init_list = std::initializer_list<Component_type>;

 private:
  static constexpr size_type kMaxType = 512;
  using Mask = std::bitset<kMaxType>;

 public:
  Component_mask() = default;
  explicit Component_mask(Init_list l);

  bool operator==(const Component_mask& rhs) const noexcept;
  bool operator!=(const Component_mask& rhs) const noexcept;
  Component_mask operator&(const Component_mask& rhs) const noexcept;
  Component_mask operator|(const Component_mask& rhs) const noexcept;
  static constexpr size_type get_max_type();

 private:
  Component_mask(const Mask& mask);

 private:
  Mask mask_;
};
}  // namespace ecs

namespace ecs {
inline constexpr typename Component_mask::size_type
Component_mask::get_max_type() {
  return kMaxType;
}

inline Component_mask::Component_mask(const Mask& mask):mask_(mask) {}
}  // namespace ecs