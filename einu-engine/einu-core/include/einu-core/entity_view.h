#pragma once

#include "einu-core/i_entity.h"
#include "einu-core/xnent_list.h"

namespace einu {

template <typename ComponentList>
class EntityView;

template <typename... Ts>
class EntityView<XnentList<Ts...>> {
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