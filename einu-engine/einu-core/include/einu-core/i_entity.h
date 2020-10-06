#pragma once

#include "einu-core/component_list.h"
#include "einu-core/i_component.h"
#include "einu-core/internal/component_index_list.h"

namespace einu {

using EID = std::size_t;

class IEntity {
 public:
  template <typename... Ts>
  bool HasComponents() const noexcept {
    return HasComponents(
        internal::GetComponentIndexList(ComponentList<Ts...>{}));
  }

  template <typename T>
  const T& GetComponent() const noexcept {
    return static_cast<const T&>(
        internal::GetComponent(GetComponentIndex<T>()));
  }

  template <typename T>
  T& GetComponent() noexcept {
    return static_cast<T&>(GetComponent(GetComponentIndex<T>()));
  }

  template <typename T>
  void AddComponent(T& comp) {
    AddComponent(internal::GetComponentIndex<T>(), comp);
  }

  template <typename T>
  T& RemoveComponent() noexcept {
    return static_cast<T&>(RemoveComponent(internal::GetComponentIndex<T>()));
  }

 protected:
  virtual bool HasComponents(
      const internal::ComponentIndexList& idx_list) const noexcept = 0;
  virtual const IComponent& GetComponent(
      internal::ComponentIndex idx) const noexcept = 0;
  virtual IComponent& GetComponent(internal::ComponentIndex idx) noexcept = 0;
  virtual void AddComponent(internal::ComponentIndex idx, IComponent& comp) = 0;
  virtual IComponent& RemoveComponent(
      internal::ComponentIndex idx) noexcept = 0;
};

}  // namespace einu