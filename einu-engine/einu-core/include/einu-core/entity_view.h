#pragma once

#include "einu-core/component_list.h"
#include "einu-core/i_entity.h"

namespace einu {

template <typename ComponentList>
class EntityView;

template <typename... Ts>
class EntityView<ComponentList<Ts...>> {
 public:
  EntityView(IEntity& ett) noexcept
      : ett_(ett) {}

  auto operator()() {
    return std::forward_as_tuple(ett_.GetComponent<Ts>()...);
  }

 private:
  IEntity& ett_;
};

}  // namespace einu