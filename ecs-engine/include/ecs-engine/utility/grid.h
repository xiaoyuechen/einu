#ifndef GRID_H_
#define GRID_H_

#include <array>

namespace ecs {

template <typename Cell, std::size_t size_x, std::size_t size_y>
class Grid {
 public:
  constexpr const Cell* operator[](std::size_t count_y) const noexcept;
  constexpr Cell* operator[](std::size_t count_y) noexcept;
  constexpr const Cell* begin() const noexcept;
  constexpr Cell* begin() noexcept;
  constexpr const Cell* end() const noexcept;
  constexpr Cell* end() noexcept;


  static constexpr std::size_t GetSizeX() noexcept;
  static constexpr std::size_t GetSizeY() noexcept;
  static constexpr std::size_t GetTotalCellCount() noexcept;

 private:
  std::array<Cell, GetTotalCellCount()> grid_;
};

//////////////////////////////////////////////////////////////////////////

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr const Cell* Grid<Cell, size_x, size_y>::operator[](std::size_t count_y) const
    noexcept {
  return grid_.data() + count_y * size_x;
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr Cell* Grid<Cell, size_x, size_y>::operator[](
    std::size_t count_y) noexcept {
  return const_cast<Cell*>(static_cast<const Grid&>(*this)[count_y]);
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr const Cell* Grid<Cell, size_x, size_y>::begin() const noexcept {
  return grid_.data();
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr Cell* Grid<Cell, size_x, size_y>::begin() noexcept {
  return const_cast<Cell*>(static_cast<const Grid&>(*this).begin());
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr const Cell* Grid<Cell, size_x, size_y>::end() const noexcept {
  return grid_.data() + GetTotalCellCount();
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr Cell* Grid<Cell, size_x, size_y>::end() noexcept {
  return const_cast<Cell*>(static_cast<const Grid&>(*this).end());
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr std::size_t Grid<Cell, size_x, size_y>::GetSizeX() noexcept {
  return size_x;
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr std::size_t Grid<Cell, size_x, size_y>::GetSizeY() noexcept {
  return size_y;
}

template <typename Cell, std::size_t size_x, std::size_t size_y>
inline constexpr std::size_t Grid<Cell, size_x, size_y>::GetTotalCellCount() noexcept {
  return size_x * size_y;
}

}  // namespace ecs

#endif  // GRID_H_
