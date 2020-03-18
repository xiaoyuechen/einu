#pragma once

#include "ecs-engine/extension/resource_manager/resource_manager.h"
#include "ecs-engine/graphics/texture.h"

namespace ecs {

template <typename Key>
using TextureManager = ResourceManager<Key, Texture>;

}