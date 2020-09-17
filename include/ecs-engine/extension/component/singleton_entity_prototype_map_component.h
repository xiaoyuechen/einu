#pragma once

#include <map>
#include <memory>

#include "ecs-engine/core/i_singleton_component.h"
#include "ecs-engine/extension/entity/entity_prototype.h"

namespace ecs {

template <typename Key, typename IEntityPrototype>
struct SingletonEntityPrototypeMapComponent : public ISingletonComponent {
  using PrototypePtr = std::unique_ptr<IEntityPrototype>;
  using PrototypeMap = std::map<Key, PrototypePtr>;
  PrototypeMap map{};
};

}  // namespace ecs
