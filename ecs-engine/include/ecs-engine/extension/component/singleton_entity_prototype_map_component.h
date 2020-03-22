#pragma once

#include <map>

#include "ecs-engine/core/component_tag.h"

namespace ecs {

template <typename Key, typename EntityPrototype>
struct SingletonEntityPrototypeMapComponent : public ComponentTag {
  using PrototypeMap = std::map<Key, EntityPrototype>;
  PrototypeMap map{};
};

}  // namespace ecs
