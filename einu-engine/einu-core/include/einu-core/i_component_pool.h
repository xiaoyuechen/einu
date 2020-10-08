#pragma once

#include "einu-core/xnent.h"
#include "einu-core/internal/xnent_index.h"

namespace einu {

class IComponentPool {
 public:
  template <typename T>
  T& Acquire() {
    return static_cast<T&>(Acquire(internal::GetXnentIndex<T>()));
  }

  template <typename T>
  void Release(const T& comp) noexcept {
    Release(internal::GetXnentIndex<T>(), comp);
  }

 protected:
  virtual Xnent& Acquire(internal::XnentIndex idx) = 0;
  virtual void Release(internal::XnentIndex idx,
                       const Xnent& comp) = 0;
};

}  // namespace einu