#pragma once
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/component/Component_type.h"

namespace ecs {
class Component_admin {
 public:
  template <typename T>
  using handle = Component_manager<T>*;

 private:
  using map = std::map<Component_type, std::unique_ptr<I_component_manager>>;

 public:
  template <typename T>
  void add_manager(std::unique_ptr<Component_manager<T>> m);

  template <typename T>
  [[nodiscard]] std::optional<handle<T>> get_manager();

  template <typename T>
  void remove_manager();

 private:
  map map_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline void Component_admin::add_manager(
    std::unique_ptr<Component_manager<T>> m) {
  assert(!get_manager<T>().has_value() && "component manager already exists");

  auto comp_type = type_of<T>();
  map_[comp_type] = std::move(m);
}

template <typename T>
inline std::optional<typename Component_admin::handle<T>>
Component_admin::get_manager() {
  auto t = type_of<T>();
  if (map_.find(t) != std::end(map_)) {
    return handle<T>(static_cast<Component_manager<T>*>(map_[t].get()));
  }
  return std::nullopt;
}

template <typename T>
inline void Component_admin::remove_manager() {
  assert(get_manager<T>().has_value() && "component manager does not exist");
  map_.erase(type_of<T>());
}
}  // namespace ecs