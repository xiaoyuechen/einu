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

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "einu-engine/core/xnent.h"

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

  Type type = Type::Orthographic;
  Attribute attrib{OrthographicAttrib{}};
};

glm::mat4 ProjectionMatrix(const Projection& projection) noexcept;
Projection operator*(const Projection& projection, float ratio) noexcept;
Projection operator*(float ratio, const Projection& projection) noexcept;

inline glm::mat4 ProjectionMatrix(const Projection& projection) noexcept {
  if (projection.type == Projection::Type::Orthographic) {
    const auto& ortho_attrib = projection.attrib.orthographic_attrib;
    return glm::ortho(ortho_attrib.left, ortho_attrib.right,
                      ortho_attrib.button, ortho_attrib.top, ortho_attrib.near,
                      ortho_attrib.far);
  } else {
    const auto& pers_attrib = projection.attrib.perspective_attrib;
    return glm::perspective(pers_attrib.fov, pers_attrib.aspect,
                            pers_attrib.near, pers_attrib.far);
  }
}

inline Projection operator*(const Projection& projection,
                            float ratio) noexcept {
  if (projection.type == Projection::Type::Orthographic) {
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

inline Projection operator*(float ratio,
                            const Projection& projection) noexcept {
  return projection * ratio;
}

struct View {
  glm::vec3 position{0, 0, 10}, target{0, 0, 0};
  glm::vec3 up{0, 1, 0};
};

inline glm::mat4 ViewMatrix(const View& view) noexcept {
  return glm::lookAt(view.position, view.target, view.up);
}

namespace cmp {

struct Camera : public Xnent {
  std::uint32_t id;
  Projection projection;
  View view;
};

}  // namespace cmp
}  // namespace graphics
}  // namespace einu
