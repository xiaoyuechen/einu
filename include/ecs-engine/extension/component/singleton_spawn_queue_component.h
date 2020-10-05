#pragma once

#include <vector>

#include "einu-engine/core/i_singleton_component.h"

namespace einu {

template <typename SpawnSetting>
struct SingletonSpawnQueueComponent : public ISingletonComponent {
  using Queue = std::vector<SpawnSetting>;
  Queue queue;
};

}  // namespace einu
