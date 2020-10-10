#pragma once

#include <functional>
#include <memory>

#include "einu-core/internal/xnent_type_id.h"
#include "einu-core/xnent.h"

namespace einu {

struct IComponentPoolPolicy {
  virtual ~IComponentPoolPolicy() = default;
};

inline constexpr std::size_t DefaultComponentPoolGrowFunc(
    std::size_t pool_size) noexcept {
  return pool_size == 0 ? 1 : 2 * pool_size;
}

template <typename Component>
struct ComponentPoolPolicy : public IComponentPoolPolicy {
  using size_type = std::size_t;
  using value_type = Component;
  using GrowFunc = std::function<size_type(size_type)>;

  ComponentPoolPolicy(size_type init_size,
                      const value_type& value = value_type{},
                      GrowFunc grow_func = DefaultComponentPoolGrowFunc)
      : init_size(init_size)
      , value(value)
      , grow_func(grow_func) {}

  size_type init_size;
  value_type value;
  GrowFunc grow_func;
};

class IComponentPool {
 public:
  virtual ~IComponentPool() = default;

  template <typename T>
  void AddPolicy(const ComponentPoolPolicy<T>& policy,
                 internal::XnentTypeID id = internal::GetXnentTypeID<T>()) {
    AddPolicyImpl(policy, id);
  }

  template <typename T>
  T& Acquire(internal::XnentTypeID id = internal::GetXnentTypeID<T>()) {
    return static_cast<T&>(AcquireImpl(id));
  }

  template <typename T>
  void Release(const T& comp, internal::XnentTypeID id =
                                  internal::GetXnentTypeID<T>()) noexcept {
    ReleaseImpl(id, comp);
  }

 protected:
  virtual void AddPolicyImpl(const IComponentPoolPolicy& policy,
                             internal::XnentTypeID id) = 0;
  virtual Xnent& AcquireImpl(internal::XnentTypeID id) = 0;
  virtual void ReleaseImpl(internal::XnentTypeID id,
                           const Xnent& comp) noexcept = 0;
};

}  // namespace einu