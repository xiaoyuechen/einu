// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <glm/glm.hpp>

namespace einu {
namespace graphics {

struct Projection {
  enum class Type {
    Orthographic,
    Perspective,
  };

  struct OrthographicAttrib {
    float left = -1, right = 1, button = -1, top = 1;
    float near = 0.01f, far = 1000.f;
  };

  struct PerspectiveAttrib {
    float fov = 45.f;
    float aspect = 16.f / 9.f;
    float near = 0.01f, far = 1000.f;
  };

  union Attribute {
    OrthographicAttrib orthographic_attrib;
    PerspectiveAttrib perspective_attrib;
  };

  Type type = Type::ORTHOGRAPHIC;
  Attribute attrib{OrthographicAttrib{}};
};

constexpr glm::mat4 ProjectionMatrix(const Projection projection) noexcept;
constexpr Projection operator*(const Projection& projection,
                               float ratio) noexcept;
constexpr Projection operator*(float ratio,
                               const Projection& projection) noexcept;

constexpr glm::mat4 ProjectionMatrix(const Projection projection) noexcept {
  if (type == Projection::Type::ORTHOGRAPHIC) {
    const auto& ortho_attrib = attrib.orthographic_attrib;
    return glm::ortho(ortho_attrib.left, ortho_attrib.right,
                      ortho_attrib.button, ortho_attrib.top, ortho_attrib.near,
                      ortho_attrib.far);
  } else {
    const auto& pers_attrib = attrib.perspective_attrib;
    return glm::perspective(pers_attrib.fov, pers_attrib.aspect,
                            pers_attrib.near, pers_attrib.far);
  }
}

constexpr Projection operator*(const Projection& projection,
                               float ratio) noexcept {
  if (projection.type == Projection::Type::ORTHOGRAPHIC) {
    auto copy = projection;
    auto& attrib = copy.attrib.orthographic_attrib;
    attrib.left *= ratio;
    attrib.right *= ratio;
    attrib.top *= ratio;
    attrib.button *= ratio;
    return copy;
  }
  return projection;
}

constexpr Projection operator*(float ratio,
                               const Projection& projection) noexcept {
  return projection * ratio;
}

}  // namespace graphics
}  // namespace einu
