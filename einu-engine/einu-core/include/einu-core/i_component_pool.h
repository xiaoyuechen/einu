#pragma once

#include "einu-core/internal/xnent_index.h"
#include "einu-core/xnent.h"

namespace einu {

class IComponentPool {
 public:
  template <typename T>
  T& Acquire() {
    return static_cast<T&>(AcquireImpl(internal::GetXnentIndex<T>()));
  }

  template <typename T>
  void Release(const T& comp) noexcept {
    ReleaseImpl(internal::GetXnentIndex<T>(), comp);
  }

 protected:
  virtual Xnent& AcquireImpl(internal::XnentIndex idx) = 0;
  virtual void ReleaseImpl(internal::XnentIndex idx,
                           const Xnent& comp) noexcept = 0;
};

}  // namespace einu