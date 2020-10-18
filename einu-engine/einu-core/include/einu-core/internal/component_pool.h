#pragma once

#include <einu-util/object_pool.h>

#include <array>
#include <cassert>
#include <tuple>
#include <variant>

#include "einu-core/i_component_pool.h"
#include "einu-core/xnent_list.h"

namespace einu {
namespace internal {

template <typename Comp>
class OneComponentPool {
 public:
  using size_type = std::size_t;
  using GrowthFunc = std::function<size_type(size_type)>;

  void SetValue(const Xnent& value) noexcept {
    auto& v = reinterpret_cast<const Comp&>(value);
    pool_.SetValue(v);
  }

  void SetGrowth(GrowthFunc growth) noexcept { pool_.SetGrowth(growth); }

  void GrowExtra(size_type delta_size) { pool_.GrowExtra(delta_size); }

  Xnent& Acquire() { return pool_.Acquire(); }

  void Release(const Xnent& obj) noexcept {
    auto& comp = reinterpret_cast<const Comp&>(obj);
    pool_.Release(comp);
  }

  size_type Size() const noexcept { return pool_.Size(); }

 private:
  using Pool = util::DynamicPool<Comp>;
  Pool pool_;
};

template <typename ComponentList>
class ComponentPool;

template <typename... Comps>
class ComponentPool<XnentList<Comps...>> final : public IComponentPool {
 public:
  ComponentPool()
      : pool_table_{OneComponentPool<Comps>{}...} {}

 private:
  using TypeList = tmp::TypeList<Comps...>;
  using PoolVariant = std::variant<OneComponentPool<Comps>...>;
  using PoolTable = std::array<PoolVariant, tmp::Size<TypeList>::value>;

  void AddPolicyImpl(size_type init_size, const Xnent& value,
                     GrowthFunc growth_func,
                     internal::XnentTypeID id) override {
    std::visit(
        [=](auto&& arg) {
          arg.SetValue(value);
          arg.SetGrowth(growth_func);
          arg.GrowExtra(init_size);
        },
        pool_table_[id]);
  }

  Xnent& AcquireImpl(internal::XnentTypeID id) override {
    return std::visit(
        [](auto&& arg) -> auto& { return arg.Acquire(); }, pool_table_[id]);
  }

  void ReleaseImpl(internal::XnentTypeID id,
                   const Xnent& comp) noexcept override {
    std::visit([&comp](auto&& arg) { arg.Release(comp); }, pool_table_[id]);
  }

  size_type OnePoolSizeImpl(internal::XnentTypeID id) const noexcept override {
    return std::visit([](auto&& arg) { return arg.Size(); }, pool_table_[id]);
  }

  PoolTable pool_table_;
};

}  // namespace internal
}  // namespace einu
