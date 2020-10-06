#pragma once

#include "einu-core/component_list.h"
#include "einu-core/entity_buffer.h"
#include "einu-core/entity_view.h"
#include "einu-core/i_component.h"
#include "einu-core/i_component_pool.h"
#include "einu-core/i_entity.h"
#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world.h"

namespace einu {

struct ExampleEnginePolicy {
  using ComponentList = ComponentList<IComponent>;
};

template <typename EnginePolicy>
class EinuEngine {
 public:
  using ComponentList = typename EnginePolicy::ComponentList;

  EinuEngine(EnginePolicy policy) {
    RequireComponentsUnique(ComponentList{});
    RegisterComponents(ComponentList{});
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
  static constexpr void RequireComponentsUnique(
      einu::ComponentList<Ts...>) noexcept {
    static_assert(((tmp::CountType<ComponentList, Ts>::value == 1) && ...),
                  "Component must be unique");
  }

  template <typename... Ts>
  static void RegisterComponents(einu::ComponentList<Ts...>) noexcept {
    auto idx = std::size_t{0};
    (internal::SetComponentIndex<Ts>(internal::ComponentIndex{idx++}), ...);
  }
};

}  // namespace einu