#pragma once
#include "ecs-core/manager/Component_manager.h"

namespace ecs {
template <typename T>
class Component_handle {
 public:
  Component_handle(T& comp,
                   const Entity_id& entity,
                   Component_manager<T>& manager);
  T* operator->();
  const T* operator->() const;
  T& operator*();
  const T& operator*() const;
  const Entity_id& get_owner() const;
  void destroy();

 private:
  T& comp_;
  Entity_id entity_;
  Component_manager<T>& manager_;
};
}  // namespace ecs

namespace ecs {
template <typename T>
inline Component_handle<T>::Component_handle(T& comp,
                                          const Entity_id& entity,
                                          Component_manager<T>& manager)
    : comp_(comp)
    , entity_(entity)
    , manager_(manager) {}

template <typename T>
inline T* Component_handle<T>::operator->() {
  return &comp_;
}

template <typename T>
inline const T* Component_handle<T>::operator->() const {
  return &comp_;
}

template <typename T>
inline T& Component_handle<T>::operator*() {
  return comp_;
}

template <typename T>
inline const T& Component_handle<T>::operator*() const {
  return comp_;
}

template <typename T>
inline const Entity_id& Component_handle<T>::get_owner() const {
  return entity_;
}

template <typename T>
inline void Component_handle<T>::destroy() {
  manager_.remove(entity_);
}
}  // namespace ecs