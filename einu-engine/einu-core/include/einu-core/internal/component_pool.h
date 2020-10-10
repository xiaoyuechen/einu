#pragma once

#include <einu-util/object_pool.h>

#include <array>
#include <cassert>
#include <tuple>

#include "einu-core/i_component_pool.h"
#include "einu-core/xnent_list.h"

namespace einu {
namespace internal {

class IOneComponentPool {
 public:
  using size_type = std::size_t;
  using GrowthFunc = std::function<size_type(size_type)>;

  virtual void SetValue(const Xnent& value) noexcept = 0;
  virtual void SetGrowth(GrowthFunc growth) noexcept = 0;
  virtual void GrowExtra(size_type delta_size) = 0;
  [[nodiscard]] virtual Xnent& Acquire() = 0;
  virtual void Release(const Xnent& obj) noexcept = 0;
  virtual size_type Size() const noexcept = 0;
};

template <typename Comp>
class OneComponentPool : public IOneComponentPool {
 public:
  void SetValue(const Xnent& value) noexcept override final {
    auto& v = reinterpret_cast<const Comp&>(value);
    pool_.SetValue(v);
  }

  void SetGrowth(GrowthFunc growth) noexcept override final {
    pool_.SetGrowth(growth);
  }

  void GrowExtra(size_type delta_size) override final {
    pool_.GrowExtra(delta_size);
  }

  Xnent& Acquire() override final { return pool_.Acquire(); }

  void Release(const Xnent& obj) noexcept override {
    auto& comp = reinterpret_cast<const Comp&>(obj);
    pool_.Release(comp);
  }

  size_type Size() const noexcept override { return pool_.Size(); }

 private:
  using Pool = util::DynamicPool<Comp>;
  Pool pool_;
};

template <typename ComponentList>
class ComponentPool;

template <typename... Comps>
class ComponentPool<XnentList<Comps...>> : public IComponentPool {
 public:
  ComponentPool() {
    (
        [&] {
          auto& pool = std::get<OneComponentPool<Comps>>(pool_tuple_);
          auto id = tmp::IndexOf<TypeList, Comps>::value;
          pool_table_[id] = &pool;
        }(),
        ...);
  }

 private:
  using TypeList = tmp::TypeList<Comps...>;
  using PoolTuple = std::tuple<OneComponentPool<Comps>...>;
  using PoolTable = std::array<IOneComponentPool*, tmp::Size<TypeList>::value>;

  virtual void AddPolicyImpl(size_type init_size, const Xnent& value,
                             GrowthFunc growth_func,
                             internal::XnentTypeID id) override final {
    auto pool = pool_table_[id];
    pool->SetValue(value);
    pool->SetGrowth(growth_func);
    pool->GrowExtra(init_size);
  }

  virtual Xnent& AcquireImpl(internal::XnentTypeID id) override final {
    return pool_table_[id]->Acquire();
  }

  virtual void ReleaseImpl(internal::XnentTypeID id,
                           const Xnent& comp) noexcept override final {
    pool_table_[id]->Release(comp);
  }

  virtual size_type OnePoolSizeImpl(
      internal::XnentTypeID id) const noexcept override final {
    return pool_table_[id]->Size();
  }

  PoolTuple pool_tuple_;
  PoolTable pool_table_;
};

}  // namespace internal
}  // namespace einu
