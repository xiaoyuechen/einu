#pragma once

#include <cstddef>
#include <functional>

namespace ecs {

class EntityID {
 public:
  constexpr EntityID() noexcept {}
  constexpr explicit EntityID(std::size_t id) noexcept
      : id_(id) {}

 private:
  std::size_t id_ = ~std::size_t(0);

  friend constexpr bool operator==(EntityID lhs, EntityID rhs) noexcept;
  friend struct std::less<ecs::EntityID>;
};

constexpr bool operator==(EntityID lhs, EntityID rhs) noexcept {
  return lhs.id_ == rhs.id_;
}

constexpr bool operator!=(EntityID lhs, EntityID rhs) noexcept {
  return !(lhs == rhs);
}

}  // namespace ecs

namespace std {
template <>
struct less<ecs::EntityID> {
  constexpr bool operator()(ecs::EntityID lhs, ecs::EntityID rhs) const noexcept {
    return lhs.id_ < rhs.id_;
  }
};
}  // namespace std
