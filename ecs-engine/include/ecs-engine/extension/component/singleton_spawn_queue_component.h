#pragma once

#include <vector>

namespace ecs {

template <typename SpawnSetting>
struct SingletonSpawnQueueComponent {
  using Queue = std::vector<SpawnSetting>;
  Queue queue;
};

}  // namespace ecs
