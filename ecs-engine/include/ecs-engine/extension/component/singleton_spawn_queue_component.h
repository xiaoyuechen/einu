#pragma once

#include <vector>

#include "ecs-engine/core/i_singleton_component.h"

namespace ecs {

template <typename SpawnSetting>
struct SingletonSpawnQueueComponent : public ISingletonComponent {
  using Queue = std::vector<SpawnSetting>;
  Queue queue;
};

}  // namespace ecs
