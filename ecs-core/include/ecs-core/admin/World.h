#pragma once
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include "ecs-core/manager/Component_manager.h"
#include "ecs-core/manager/Entity_manager.h"
#include "ecs-core/manager/Entity_handle.h"

namespace ecs {
class I_system;
class World {
 private:
  using sys_ptr = std::unique_ptr<I_system>;
  template <typename T>
  using mgr_ptr = std::unique_ptr<T>;
  using time = float;

 public:
  World() = default;

  // system
  void add_system(sys_ptr s);

  // component
  template <typename T>
  [[nodiscard]] Component_manager<T>& get_manager();
  template <typename T>
  void add_manager(std::unique_ptr<Component_manager<T>> m);
  template <typename T>
  void remove_manager();

  template <typename T>
  T& get_component(const Entity_id& e);
  template <typename T>
  T& add_component(const Entity_id& e);
  template <typename T>
  void remove_component(const Entity_id& e);

  // entity
  Entity_handle create_entity();

  // update
  void update(time dt);

 private:
  std::vector<sys_ptr> sys_arr_;
  Entity_manager ett_mgr_;
};
}  // namespace ecs

namespace ecs {
inline void World::add_system(sys_ptr s) {
  sys_arr_.push_back(std::move(s));
}

template <typename T>
inline void World::add_manager(std::unique_ptr<Component_manager<T>> m) {
  ett_mgr_;
}

template <typename T>
inline void World::remove_manager() {
  ett_mgr_;
}

template <typename T>
inline T& World::get_component(const Entity_id& e) {
  auto& m = get_manager<T>();
  auto& c = m.get_component(e);
  return c;
}

template <typename T>
inline T& World::add_component(const Entity_id& e) {
  auto& m = get_manager<T>();
  auto& c = m.get_component(e);
  return c;
}

template <typename T>
inline void World::remove_component(const Entity_id& e) {
  auto& m = get_manager<T>();
  m.remove_component(e);
}
}  // namespace ecs