#pragma once

#include <tuple>
#include <vector>

#include "entity_data_vector.h"

namespace ecs {

template <typename... Ts>
class ComponentEntityBuffer {
 public:
  using ComponentTuple = std::tuple<Ts&...>;
  using ComponentTupleBuffer = std::vector<ComponentTuple>;
  using EntityDataBuffer = EntityDataVector;

  void Clear() noexcept {
    comps.clear();
    etts.clear();
  }

  const ComponentTupleBuffer& GetComponents() const noexcept { return comps; }
  ComponentTupleBuffer& GetComponents() noexcept { return comps; }
  const EntityDataBuffer& GetEntities() const noexcept { return etts; }
  EntityDataBuffer& GetEntities() noexcept { return etts; }

 private:
  ComponentTupleBuffer comps;
  EntityDataBuffer etts;
};

}  // namespace ecs