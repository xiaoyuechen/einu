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

#include <array>
#include <cstdint>
#include <glm/glm.hpp>
#include <initializer_list>

namespace einu {
namespace graphics {

template <typename T = std::uint8_t, std::size_t channel_count = 4>
class Color {
 public:
  static constexpr std::size_t kChannelCount = channel_count;
  using Value = T;
  using InitializerList = std::initializer_list<T>;
  using Storage = glm::vec<channel_count, T>;

  Color() noexcept {}
  // NOLINTNEXTLINE
  Color(InitializerList il) { std::copy(il.begin(), il.end(), &storage_[0]); }
  explicit Color(const Storage& storage) : storage_(storage) {}

  auto operator[](std::size_t idx) const noexcept { return storage_[idx]; }
  auto& operator[](std::size_t idx) noexcept { return storage_[idx]; }

  auto R() const noexcept { return storage_[0]; }
  auto& R() noexcept { return storage_[0]; }
  auto G() const noexcept { return storage_[1]; }
  auto& G() noexcept { return storage_[1]; }
  auto B() const noexcept { return storage_[2]; }
  auto& B() noexcept { return storage_[2]; }
  auto A() const noexcept { return storage_[3]; }
  auto& A() noexcept { return storage_[3]; }

  auto GetScaled(float scale) const {
    auto vec = glm::vec<channel_count, float>(storage_) * scale;
    return Color<float, channel_count>(vec);
  }

 private:
  Storage storage_{0};
};

template <typename Color, typename Max>
auto ScaleZeroOne(const Color& color, Max max) {
  return color.GetScaled(1.f / max);
}

}  // namespace graphics
}  // namespace einu
