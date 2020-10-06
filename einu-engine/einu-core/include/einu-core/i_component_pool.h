#pragma once

#include "einu-core/i_component.h"
#include "einu-core/internal/component_index.h"

namespace einu {

class IComponentPool {
 public:
  template <typename T>
  T& Acquire() {
    return static_cast<T&>(Acquire(internal::GetComponentIndex<T>()));
  }

  template <typename T>
  void Release(const T& comp) noexcept {
    Release(internal::GetComponentIndex<T>(), comp);
  }

 protected:
  virtual IComponent& Acquire(internal::ComponentIndex idx) = 0;
  virtual void Release(internal::ComponentIndex idx,
                       const IComponent& comp) = 0;
};

}  // namespace einu