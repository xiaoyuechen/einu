#pragma once
#include <cstddef>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include "ecs-core/utility/util.h"
#include "I_component.h"

namespace ecs {
class Component_type {
 public:
  using id_type = std::size_t;

 public:
  constexpr explicit Component_type(id_type id) noexcept;
  constexpr bool operator==(const Component_type& rhs) const noexcept;
  constexpr bool operator!=(const Component_type& rhs) const noexcept;
  constexpr bool operator<(const Component_type& rhs) const noexcept;
  constexpr id_type id() const noexcept;

 private:
  id_type id_ = 0;
};

template <typename T>
Component_type type_of();
}  // namespace ecs

namespace ecs {
inline constexpr Component_type::Component_type(id_type id) noexcept
    : id_(id) {}

inline constexpr bool Component_type::operator==(
    const Component_type& rhs) const noexcept {
  return id() == rhs.id();
}

inline constexpr bool Component_type::operator!=(
    const Component_type& rhs) const noexcept {
  return !(*this == rhs);
}

inline constexpr bool Component_type::operator<(
    const Component_type& rhs) const noexcept {
  return id() < rhs.id();
}

inline constexpr typename Component_type::id_type Component_type::id() const
    noexcept {
  return id_;
}

template <typename T>
Component_type type_of() {
  static_assert(std::is_base_of<I_component, T>() &&
                "T must inherit from Component class");
  return Component_type(typeid(T).hash_code());
}
}  // namespace ecs