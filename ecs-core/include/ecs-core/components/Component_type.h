#pragma once
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include "ecs-core/utilities/util.h"

namespace ecs {
class Component_type {
 public:
  using size_type = std::size_t;

 public:
  constexpr explicit Component_type(size_type id) noexcept;

  constexpr size_type id() const noexcept;

 private:
  size_type id_ = 0;
};

template <typename T>
Component_type type_of();
}  // namespace ecs

namespace ecs {
inline constexpr Component_type::Component_type(size_type id) noexcept
    : id_(id) {}

inline constexpr typename Component_type::size_type Component_type::id() const
    noexcept {
  return id_;
}

namespace {
class Id_manager {
 public:
  using size_type = std::size_t;

 public:
  Id_manager(const Id_manager&) = delete;
  Id_manager& operator=(const Id_manager&) = delete;
  static Id_manager& get_instance();
  template <typename T>
  size_type gen_id();

 private:
  Id_manager() = default;

 private:
  std::mutex mutex_{};
  size_type type_counter_ = 0;
  std::unordered_map<std::type_index, size_type> type_id_map_{};
};
}  // namespace

template <typename T>
Component_type type_of() {
  auto& id_manager = Id_manager::get_instance();
  return Component_type(id_manager.gen_id<T>());
}

inline Id_manager& Id_manager::get_instance() {
  static Id_manager manager{};
  return manager;
}

template <typename T>
typename Id_manager::size_type Id_manager::gen_id() {
  auto type_index = util::get_type_index<T>();
  if (type_id_map_.find(type_index) == std::end(type_id_map_)) {
    auto lock = std::scoped_lock(mutex_);
    type_id_map_[type_index] = type_counter_++;
  }
  return type_id_map_[type_index];
}
}  // namespace ecs

namespace std {
template <>
struct less<ecs::Component_type> {
  bool operator()(const ecs::Component_type& lhs,
                  const ecs::Component_type& rhs) const {
    return lhs.id() < rhs.id();
  }
};
}  // namespace std