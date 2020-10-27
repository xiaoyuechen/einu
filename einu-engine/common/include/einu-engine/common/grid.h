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
#include <vector>

namespace einu {
namespace common {

template <typename T>
class Grid {
 public:
  Grid() = default;
  explicit Grid(glm::uvec2 size);

  const T* operator[](std::size_t y) const noexcept;
  T* operator[](std::size_t y) noexcept;
  const T* begin() const noexcept;
  T* begin() noexcept;
  const T* end() const noexcept;
  T* end() noexcept;
  void GetCells(std::size_t x, std::size_t y, std::size_t x_count,
                std::size_t y_count, const T** dest) const;

  glm::uvec2 GetSize() const noexcept;
  std::size_t GetTotalCellCount() const noexcept;

 private:
  glm::uvec2 size_;
  std::vector<T> grid_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T>
inline Grid<T>::Grid(glm::uvec2 size) {
  size_ = size;
  grid_.resize(GetTotalCellCount());
}

template <typename T>
inline const T* Grid<T>::operator[](std::size_t y) const noexcept {
  return grid_.data() + y * size_.x;
}

template <typename T>
inline T* Grid<T>::operator[](std::size_t y) noexcept {
  return const_cast<T*>(static_cast<const Grid&>(*this)[y]);
}

template <typename T>
inline const T* Grid<T>::begin() const noexcept {
  return grid_.data();
}

template <typename T>
inline T* Grid<T>::begin() noexcept {
  return const_cast<T*>(static_cast<const Grid&>(*this).begin());
}

template <typename T>
inline const T* Grid<T>::end() const noexcept {
  return grid_.data() + GetTotalCellCount();
}

template <typename T>
inline T* Grid<T>::end() noexcept {
  return const_cast<T*>(static_cast<const Grid&>(*this).end());
}

template <typename T>
inline void Grid<T>::GetCells(std::size_t pos_x, std::size_t pos_y,
                              std::size_t count_x, std::size_t count_y,
                              const T** dest) const {
  for (std::size_t y_index = 0; y_index != count_y; ++y_index) {
    for (std::size_t x_index = 0; x_index != count_x; ++x_index) {
      dest[x_index + y_index * count_x] =
          &(*this)[pos_y + y_index][pos_x + x_index];
    }
  }
}

template <typename T>
inline glm::uvec2 Grid<T>::GetSize() const noexcept {
  return size_;
}

template <typename T>
inline std::size_t Grid<T>::GetTotalCellCount() const noexcept {
  return static_cast<std::size_t>(size_.x) * size_.y;
}

}  // namespace common
}  // namespace einu
