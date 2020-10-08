#pragma once

#include "einu-core/component_list.h"
#include "einu-core/entity_buffer.h"
#include "einu-core/entity_view.h"
#include "einu-core/i_component.h"
#include "einu-core/i_component_pool.h"
#include "einu-core/i_entity.h"
#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world.h"
#include "einu-core/singlenent_list.h"

namespace einu {

template <typename ComponentList, typename SinglenentList>
struct EnginePolicy;

template <typename... Components, typename... Singlenents>
struct EnginePolicy<ComponentList<Components...>,
                    SinglenentList<Singlenents...>> {
  using ComponentList = ComponentList<Components...>;
  using SinglenentList = SinglenentList<Singlenents...>;
};

template <typename EnginePolicy>
class EinuEngine {
 public:
  using ComponentList = typename EnginePolicy::ComponentList;
  using SinglenentList = typename EnginePolicy::SinglenentList;

  EinuEngine(EnginePolicy policy) {
    RequireUnique(ComponentList{});
    RequireUnique(SinglenentList{});
    RegisterComponents(ComponentList{});
    RegisterSinglenents(SinglenentList{});
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
  static constexpr auto kCompCount = tmp::Size<ComponentList>::value;
  // using ComponentMask = std::bitset<kCompCount>;

  template <typename... Ts>
  static constexpr void RequireUnique(tmp::TypeList<Ts...>) noexcept {
    static_assert(
        ((tmp::CountType<tmp::TypeList<Ts...>, Ts>::value == 1) && ...),
        "Type must be unique");
  }

  template <typename... Ts>
  static void RegisterComponents(einu::ComponentList<Ts...>) noexcept {
    auto idx = std::size_t{0};
    (internal::SetComponentIndex<Ts>(internal::ComponentIndex{idx++}), ...);
  }

  template <typename... Ts>
  static void RegisterSinglenents(einu::SinglenentList<Ts...>) noexcept {
    auto idx = std::size_t{0};
    (internal::SetSinglenentIndex<Ts>(internal::SinglenentIndex{idx++}), ...);
  }
};

}  // namespace einu