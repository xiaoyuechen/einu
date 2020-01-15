#pragma once
#include "ecs-core/component/Component_mask.h"
#include "ecs-core/entity/Entity.h"
#include <map>

namespace ecs {
class Component_mask_manager {
 private:
  using map = std::map<Entity, Component_mask>;

 public:
  template <typename T>
  void add(const Entity& e);
  template <typename T>
  void remove(const Entity& e);
  const Component_mask& get(const Entity& e) const;

 private:
  map map_;
};
}  // namespace ecs

namespace ecs{
template <typename T>
inline void Component_mask_manager::add(const Entity& e) {  
  map_[e].set(type_of<T>());
}

template <typename T>
inline void Component_mask_manager::remove(const Entity& e) {
  map_[e].reset(type_of<T>());
}

inline const Component_mask& ecs::Component_mask_manager::get(const Entity& e) const {
  return map_.at(e);
}
}  // namespace ecs