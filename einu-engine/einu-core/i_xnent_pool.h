#pragma once

#include "einu-core/internal/pool_policy.h"
#include "einu-core/xnent.h"
#include "einu-core/xnent_type_id.h"

namespace einu {

class IXnentPool {
 public:
  using size_type = std::size_t;
  template <typename Xnent>
  using Policy = internal::PoolPolicy<Xnent>;

  virtual ~IXnentPool() = default;

  template <typename T>
  void AddPolicy(const Policy<T>& policy,
                 XnentTypeID id = GetXnentTypeID<T>()) {
    AddPolicyImpl(policy.init_size, policy.value, policy.growth_func, id);
  }

  template <typename T>
  T& Acquire() {
    return static_cast<T&>(AcquireImpl(GetXnentTypeID<T>()));
  }

  Xnent& Acquire(XnentTypeID tid) { return AcquireImpl(tid); }

  template <typename T>
  void Release(T& comp) noexcept {
    ReleaseImpl(GetXnentTypeID<T>(), comp);
  }

  void Release(XnentTypeID tid, Xnent& comp) noexcept {
    ReleaseImpl(tid, comp);
  }

  template <typename T>
  size_type OnePoolSize() const noexcept {
    return OnePoolSizeImpl(GetXnentTypeID<T>());
  }

  size_type OnePoolSize(XnentTypeID tid) const noexcept {
    return OnePoolSizeImpl(tid);
  }

 protected:
  virtual void AddPolicyImpl(size_type init_size, const Xnent& value,
                             internal::GrowthFunc growth_func,
                             XnentTypeID id) = 0;
  virtual Xnent& AcquireImpl(XnentTypeID id) = 0;
  virtual void ReleaseImpl(XnentTypeID id, Xnent& comp) noexcept = 0;
  virtual size_type OnePoolSizeImpl(XnentTypeID id) const noexcept = 0;
};

}  // namespace einu