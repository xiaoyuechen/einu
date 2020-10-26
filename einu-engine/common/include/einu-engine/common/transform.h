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

namespace einu {

using Transform = glm::mat4;

class Transform {
 public:
  enum class UseCache : std::uint8_t { Yes, No };

  explicit Transform(UseCache use_cache = UseCache::Yes) noexcept {
    use_cache_ = use_cache;
  }

  glm::vec3 GetPosition() const noexcept { return glm::vec3{transform_[3]}; }

  glm::quat GetRotation() const noexcept { return rotation_; }

  glm::vec3 GetScale() const noexcept { return scale_; }

  glm::mat4 GetTransform() const noexcept {
    if (use_cache_) {
      return transform_;
    }
    return glm::translate(position_) * glm::toMat4(rotation_) *
           glm::scale(scale_);
  }

  void SetPosition(glm::vec3 position) noexcept {
    memcpy(&transform_[3], &position[0], sizeof(position));
  }

  void SetRotation(glm::quat rot) noexcept {
    if (use_cache_) {
      auto pos = GetPosition();
      transform_ = glm::toMat4(rot) * glm::scale(scale_);
      SetPosition(pos);
    }
    rotation_ = rot;
  }

  void SetScale(glm::vec3 scale) {
    if (use_cache_) {
      auto pos = GetPosition();
      transform_ = glm::toMat4(rotation_) * glm::scale(scale);
      SetPosition(pos);
    }
    scale = scale_;
  }

 private:
  glm::quat rotation_{1, 0, 0, 0};
  glm::vec3 scale_{1, 1, 1};
  glm::mat4 transform_{};
  UseCache use_cache_ = UseCache::Yes;
};

}  // namespace einu
