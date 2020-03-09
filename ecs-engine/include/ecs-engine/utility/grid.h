#ifndef GRID_H_
#define GRID_H_

#include <vector>

#include "ecs-engine/math/glm.h"

namespace ecs {

template <typename T>
class Grid {
 public:
  Grid(glm::uvec2 size);
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
inline void Grid<T>::GetCells(std::size_t x, std::size_t y, std::size_t x_count,
                              std::size_t y_count, const T** dest) const {
  for (std::size_t y_index = 0; y_index != y_count; ++y_index) {
    for (std::size_t x_index = 0; x_index != x_count; ++x_index) {
      dest[x_index + y_index * x_count] = &(*this)[x + x_index][y + y_index];
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

}  // namespace ecs

#endif  // GRID_H_
