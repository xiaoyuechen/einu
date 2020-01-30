#ifndef ENTITY_ID_H_
#define ENTITY_ID_H_

#include <cstddef>
#include <functional>

namespace ecs {

class EntityID {
 public:
  constexpr EntityID() noexcept;
  constexpr explicit EntityID(std::size_t id) noexcept;
  constexpr std::size_t GetID() const noexcept;

 private:
  std::size_t id_ = 0;
};

constexpr bool operator==(const EntityID& lhs, const EntityID& rhs) noexcept;
constexpr bool operator!=(const EntityID& lhs, const EntityID& rhs) noexcept;

}  // namespace ecs

namespace std {
template <>
struct less<ecs::EntityID>;
}

//////////////////////////////////////////////////////////////////////////
namespace ecs {

inline constexpr EntityID::EntityID() noexcept {}

inline constexpr EntityID::EntityID(std::size_t id) noexcept
    : id_(id) {}

inline constexpr std::size_t EntityID::GetID() const noexcept { return id_; }

inline constexpr bool operator==(const EntityID& lhs,
                                 const EntityID& rhs) noexcept {
  return lhs.GetID() == rhs.GetID();
}

inline constexpr bool operator!=(const EntityID& lhs,
                                 const EntityID& rhs) noexcept {
  return !(lhs == rhs);
}

}  // namespace ecs

namespace std {
template <>
struct less<ecs::EntityID> {
  bool operator()(const ecs::EntityID& lhs, const ecs::EntityID& rhs) const {
    return lhs.GetID() < rhs.GetID();
  }
};
}  // namespace std

#endif  // ENTITY_ID_H_
