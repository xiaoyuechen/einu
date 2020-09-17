#pragma once

#include <tuple>
#include <vector>

#include "ecs-engine/core/entity.h"

namespace ecs {

template <typename... Ts>
class ComponentEntityBuffer {
 public:
  using ComponentTuple = std::tuple<Ts&...>;
  using ComponentTupleBuffer = std::vector<ComponentTuple>;
  using EntityBuffer = std::vector<std::reference_wrapper<IEntity>>;

  void Clear() noexcept {
    comps_.clear();
    etts_.clear();
  }

  const ComponentTupleBuffer& GetComponents() const noexcept { return comps_; }
  ComponentTupleBuffer& GetComponents() noexcept { return comps_; }
  const EntityBuffer& GetEntities() const noexcept { return etts_; }
  EntityBuffer& GetEntities() noexcept { return etts_; }

 private:
  ComponentTupleBuffer comps_;
  EntityBuffer etts_;
};

}  // namespace ecs