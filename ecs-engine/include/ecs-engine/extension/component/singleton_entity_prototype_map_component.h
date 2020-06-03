#pragma once

#include <map>

#include "ecs-engine/core/component.h"

namespace ecs {

template <typename Key, typename EntityPrototype>
struct SingletonEntityPrototypeMapComponent : public IComponent {
  using PrototypeMap = std::map<Key, EntityPrototype>;
  PrototypeMap map{};
};

}  // namespace ecs
