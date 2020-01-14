#pragma once
#include <map>
#include <typeindex>
#include <vector>
#include "ecs-core/components/Component.h"
#include "ecs-core/components/Component_mask.h"

namespace ecs {
class Entity {
 public:
  using size_type = std::size_t;

 public:
  constexpr explicit Entity(size_type id) noexcept;
  constexpr size_type id() const noexcept;
  constexpr bool operator==(const Entity& rhs) const noexcept;

 private:
  size_type id_;
};

inline constexpr Entity::Entity(size_type id) noexcept
    : id_(id) {}

inline constexpr typename Entity::size_type Entity::id() const noexcept {
  return id_;
}

inline constexpr bool Entity::operator==(const Entity& rhs) const noexcept {
  return id() == rhs.id();
}
}  // namespace ecs

namespace std {
template <>
struct less<ecs::Entity> {
  bool operator()(const ecs::Entity& lhs, const ecs::Entity& rhs) const {
    return lhs.id() < rhs.id();
  }
};
}  // namespace std