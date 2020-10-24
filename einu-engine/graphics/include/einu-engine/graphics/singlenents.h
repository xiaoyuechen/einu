#pragma once

#include <absl/container/flat_hash_map.h>
#include <einu-engine/core/xnent.h>

#include <array>
#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <utility>

#include "einu-engine/graphics/resource_type.h"

namespace einu {
namespace graphics {
namespace sgln {

struct Camera : public Xnent {
  std::uint32_t active_camera;
};

struct ResourceTable : public Xnent {
  using Key = std::pair<ResourceType, std::string>;
  using Value = std::uint32_t;
  using Table = absl::flat_hash_map<Key, Value>;

  Table table;
};

}  // namespace sgln
}  // namespace graphics
}  // namespace einu
