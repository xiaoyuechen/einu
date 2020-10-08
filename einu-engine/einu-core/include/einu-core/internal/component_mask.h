#pragma once

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <memory>
#include <vector>

#include "einu-core/component_list.h"
#include "einu-core/internal/component_index.h"

namespace einu {
namespace internal {

class ComponentMask {
 public:
  using size_type = std::size_t;

  template <typename... Ts>
  explicit ComponentMask(ComponentList<Ts...>) {
    using namespace std;
    auto max_idx =
        max({ComponentIndex::IndexType(internal::GetComponentIndex<Ts>())...});
    size_ = (max_idx + 8) / 8;
    data_ = std::make_unique<uint8_t[]>(size_);
    ((*(data_.get() + internal::GetComponentIndex<Ts>() / 8) |=
      uint8_t{1} << (internal::GetComponentIndex<Ts>() % 8)),
     ...);
  }

  const std::uint8_t* Data() const noexcept { return data_.get(); }
  size_type SizeInBytes() const noexcept { return size_; }

 private:
  std::unique_ptr<std::uint8_t[]> data_;
  std::size_t size_;
};

template <typename... Ts>
const ComponentMask& GetComponentMask(ComponentList<Ts...> comp_list) {
  static auto& idx_list = *new ComponentMask(comp_list);
  return idx_list;
}

template <std::size_t max_comp>
using StaticComponentMask = std::bitset<max_comp>;

template <std::size_t max_comp>
StaticComponentMask<max_comp> ToStatic(const ComponentMask& mask) noexcept {
  auto r = StaticComponentMask<max_comp>{};
  std::copy(mask.Data(), mask.Data() + mask.SizeInBytes(), &r);
  return r;
}

template <std::size_t max_comp>
bool operator==(const ComponentMask& mask,
                const StaticComponentMask<max_comp>& smask) noexcept {
  return ToStatic<max_comp>(mask) == smask;
}

template <std::size_t max_comp>
bool operator==(const StaticComponentMask<max_comp>& smask,
                const ComponentMask& mask) noexcept {
  return mask == smask;
}

template <std::size_t max_comp>
StaticComponentMask<max_comp> operator&(
    const ComponentMask& mask,
    const StaticComponentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r &= smask;
  return r;
}

template <std::size_t max_comp>
StaticComponentMask<max_comp> operator&(
    const StaticComponentMask<max_comp>& smask,
    const ComponentMask& mask) noexcept {
  return mask & smask;
}

template <std::size_t max_comp>
StaticComponentMask<max_comp> operator|(
    const ComponentMask& mask,
    const StaticComponentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r |= smask;
  return r;
}

template <std::size_t max_comp>
StaticComponentMask<max_comp> operator|(
    const StaticComponentMask<max_comp>& smask,
    const ComponentMask& mask) noexcept {
  return mask | smask;
}

}  // namespace internal
}  // namespace einu