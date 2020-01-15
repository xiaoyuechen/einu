#pragma once
#include <cstddef>
#include <functional>

namespace ecs {
class Entity_id {
 public:
  using size_type = std::size_t;

 public:
  constexpr Entity_id() noexcept;
  constexpr explicit Entity_id(size_type id) noexcept;
  constexpr size_type id() const noexcept;
  constexpr bool operator==(const Entity_id& rhs) const noexcept;
  constexpr bool operator!=(const Entity_id& rhs) const noexcept;

 private:
  size_type id_ = 0;
};
}  // namespace ecs

namespace ecs {
inline constexpr Entity_id::Entity_id() noexcept {}

inline constexpr Entity_id::Entity_id(size_type id) noexcept
    : id_(id) {}

inline constexpr typename Entity_id::size_type Entity_id::id() const noexcept {
  return id_;
}

inline constexpr bool Entity_id::operator==(const Entity_id& rhs) const noexcept {
  return id() == rhs.id();
}
inline constexpr bool Entity_id::operator!=(const Entity_id& rhs) const noexcept {
  return !(*this == rhs);
}
}  // namespace ecs

namespace std {
template <>
struct less<ecs::Entity_id> {
  bool operator()(const ecs::Entity_id& lhs, const ecs::Entity_id& rhs) const {
    return lhs.id() < rhs.id();
  }
};
}  // namespace std