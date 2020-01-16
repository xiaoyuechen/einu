#pragma once
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/component/Component_type.h"
#include <memory>

namespace ecs {
class Component_manager_admin {
 private:
  using map = std::map<Component_type, std::unique_ptr<I_component_manager>>;

 public:
  template <typename T>
  void add_manager(std::unique_ptr<Component_manager<T>> m);
  template <typename T>
  [[nodiscard]] Component_manager<T>& get_manager();
  template <typename T>
  void remove_manager();

 private:
  map map_;
};


template <typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size);
}  // namespace ecs

namespace ecs {
template <typename T>
inline void Component_manager_admin::add_manager(
    std::unique_ptr<Component_manager<T>> m) {
  map_.insert(std::move(std::make_pair(type_of<T>(), std::move(m))));
}

template <typename T>
inline Component_manager<T>& Component_manager_admin::get_manager() {
  return static_cast<Component_manager<T>&>(*(map_.at(type_of<T>())));
}

template <typename T>
inline void Component_manager_admin::remove_manager() {
  map_.erase(type_of<T>());
}

template <typename T>
std::unique_ptr<Component_manager<T>> create_component_manager(
    size_t pool_size) {
  auto p = std::make_unique<typename Component_manager<T>::Pool>(pool_size);
  auto m = std::make_unique<Component_manager<T>>(std::move(p));
  return m;
}
}  // namespace ecs