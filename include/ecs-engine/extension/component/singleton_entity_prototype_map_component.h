#pragma once

#include <map>
#include <memory>

#include "einu-engine/core/i_singleton_component.h"
#include "einu-engine/extension/entity/entity_prototype.h"

namespace einu {

template <typename Key, typename IEntityPrototype>
struct SingletonEntityPrototypeMapComponent : public ISingletonComponent {
  using PrototypePtr = std::unique_ptr<IEntityPrototype>;
  using PrototypeMap = std::map<Key, PrototypePtr>;
  PrototypeMap map{};
};

}  // namespace einu
