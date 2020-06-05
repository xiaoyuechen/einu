#pragma once

#include <map>

#include "ecs-engine/core/i_singleton_component.h"

namespace ecs {

template <typename Key, typename EntityPrototype>
struct SingletonEntityPrototypeMapComponent : public ISingletonComponent {
  using PrototypeMap = std::map<Key, EntityPrototype>;
  PrototypeMap map{};
};

}  // namespace ecs
