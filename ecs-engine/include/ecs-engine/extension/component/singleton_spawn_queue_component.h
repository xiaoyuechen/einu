#pragma once

#include <vector>

namespace ecs {

template <typename SpawnSetting>
struct SingletonSpawnQueueComponent : public IComponent {
  using Queue = std::vector<SpawnSetting>;
  Queue queue;
};

}  // namespace ecs
