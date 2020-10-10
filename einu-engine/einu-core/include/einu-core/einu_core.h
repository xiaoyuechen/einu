#pragma once

#include "einu-core/entity_buffer.h"
#include "einu-core/entity_view.h"
#include "einu-core/i_component_pool.h"
#include "einu-core/i_entity.h"
#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world.h"
#include "need_list.h"

namespace einu {

template <typename NeedList>
struct EnginePolicy;

template <typename... Components, typename... Singlenents>
struct EnginePolicy<
    NeedList<XnentList<Components...>, XnentList<Singlenents...>>> {
  using NeedList =
      NeedList<XnentList<Components...>, XnentList<Singlenents...>>;
};

template <typename EnginePolicy>
class EinuEngine {
 public:
  using NeedList = typename EnginePolicy::NeedList;
  using ComponentList = typename NeedList::ComponentList;
  using SinglenentList = typename NeedList::SinglenentList;

  EinuEngine() noexcept {
    RequireUnique(ComponentList{});
    RequireUnique(SinglenentList{});
    RegisterXnents(ComponentList{});
    RegisterXnents(SinglenentList{});
  }

  ~EinuEngine() {
    ResetXnents(ComponentList{});
    ResetXnents(SinglenentList{});
  }

  std::unique_ptr<IComponentPool> CreateComponentPool() {
    // TODO(Xiaoyue Chen): create and return component pool
  }

  std::unique_ptr<IEntityPool> CreateEntityPool() {
    // TODO(Xiaoyue Chen): create and return entity pool
  }

  std::unique_ptr<IWorldFactory> CreateWorldFactory() {
    // TODO(Xiaoyue Chen): create and return world factory
  }

 private:
  static constexpr auto kCompCount =
      tmp::Size<ToTypeList<ComponentList>::Type>::value;

  template <typename... Ts>
  static constexpr void RequireUnique(XnentList<Ts...>) noexcept {
    static_assert(
        ((tmp::CountType<tmp::TypeList<Ts...>, Ts>::value == 1) && ...),
        "Type must be unique");
  }

  template <typename... Ts>
  static void RegisterXnents(XnentList<Ts...>) noexcept {
    auto idx = std::size_t{0};
    (internal::SetXnentTypeID<Ts>(internal::XnentTypeID{idx++}), ...);
  }

  template <typename... Ts>
  static void ResetXnents(XnentList<Ts...>) noexcept {
    (internal::ResetXnentTypeID<Ts>(), ...);
  }
};

}  // namespace einu