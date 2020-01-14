#pragma once
#include <algorithm>
#include <bitset>
#include <initializer_list>
#include "ecs-core/components/Component_type.h"

namespace ecs {
class Component_mask {
 public:
  using size_type = std::size_t;

 public:
  //Component_mask& add_component(Component_type type, size_t count = 1);
  //Component_mask& remove_component(Component_type type, size_t count = 1);
  static constexpr size_type get_max_type();

 private:
  static constexpr size_type kMaxType = 128;
  std::bitset<kMaxType> mask_;

  // private:
  // friend bool operator<=(const Component_mask& lhs, const Component_mask&
  // rhs); friend bool operator>=(const Component_mask& lhs, const
  // Component_mask& rhs);
};
}  // namespace ecs

namespace ecs {
inline constexpr typename Component_mask::size_type
Component_mask::get_max_type() {
  return kMaxType;
}

// bool operator<=(const Component_mask& lhs, const Component_mask& rhs) {
//  auto& l_map = lhs.type_map;
//  auto& r_map = rhs.type_map;
//  for (auto l_it = std::begin(l_map); l_it != std::end(l_map); ++l_it) {
//    auto r_it = r_map.find(l_it->first);
//    if (r_it == std::end(r_map)) return false;
//    if (r_it->second < l_it->second) return false;
//  }
//  return true;
//}
//
// bool operator>=(const Component_mask& lhs, const Component_mask& rhs) {
//  return lhs <= rhs;
//}
}  // namespace ecs