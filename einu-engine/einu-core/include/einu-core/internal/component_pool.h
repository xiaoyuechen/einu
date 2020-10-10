#pragma once

#include <einu-util/object_pool.h>

#include <tuple>

#include "einu-core/i_component_pool.h"
#include "einu-core/xnent_list.h"

namespace einu {
namespace internal {

template <typename ComponentList>
class ComponentPool;

template <typename... Comps>
class ComponentPool<XnentList<Comps...>> : public IComponentPool {
 public:
  using TypeList = tmp::TypeList<Comps...>;
  template <typename T>
  using Pool = util::DynamicPool<T>;

 private:
  virtual void AddPolicyImpl(const IComponentPoolPolicy& policy,
                             internal::XnentTypeID id) override final {
    (
        [&] {
          if (tmp::IndexOf<TypeList, Comps>::value == id) {
            auto plc = reinterpret_cast<const ComponentPoolPolicy<Comps>&>(policy);
            auto& pool = std::get<Pool<Comps>>(pools_);
            //auto plc_ptr = std::make_unique()
            //pool.SetGrowPolicy()
          }
        }(),
        ...);
  }

  virtual Xnent& AcquireImpl(internal::XnentTypeID id) override final {
    throw std::logic_error("The method or operation is not implemented.");
  }

  virtual void ReleaseImpl(internal::XnentTypeID id,
                           const Xnent& comp) noexcept override final {
    throw std::logic_error("The method or operation is not implemented.");
  }

  using PoolTuple = std::tuple<Pool<Comps>...>;
  PoolTuple pools_;
};

}  // namespace internal
}  // namespace einu
