#pragma once

#include <absl/container/flat_hash_map.h>
#include <einu-core/xnent.h>

#include <array>
#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <utility>

namespace einu {
namespace graphics {
namespace sgln {

struct Camera : public Xnent {
  std::uint32_t active_camera;
};

struct ResourceTable : public Xnent {
  enum class Type {
    VertexShader,
    FragmentShader,
    ShaderProgram,
    Texture,
    VertexArray,
    VertexBuffer,
    Count
  };

  using Key = std::pair<Type, std::string>;
  using Value = std::uint32_t;
  using Table = absl::flat_hash_map<Key, Value>;

  Table table;
};

}  // namespace sgln
}  // namespace graphics
}  // namespace einu