#pragma once

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

#include "einu-core/xnent_type_id.h"
#include "einu-core/xnent_list.h"

namespace einu {
namespace internal {

class DynamicXnentMask {
 public:
  using size_type = std::size_t;
  using initializer_list = std::initializer_list<XnentTypeID>;

  DynamicXnentMask(initializer_list init) {
    size_ = (std::max(init) + 8) / 8;
    data_ = std::make_unique<uint8_t[]>(size_);
    std::for_each(init.begin(), init.end(), [&](auto id) {
      *(data_.get() + id / 8) |= uint8_t{1} << (id % 8);
    });
  }

  const std::uint8_t* Data() const noexcept { return data_.get(); }
  size_type SizeInBytes() const noexcept { return size_; }

 private:
  std::unique_ptr<std::uint8_t[]> data_;
  std::size_t size_;
};

namespace detail {
template <typename... Ts>
const DynamicXnentMask& GetXnentMaskImpl(XnentList<Ts...>) {
  static auto& r = *new DynamicXnentMask{GetXnentTypeID<Ts>()...};
  return r;
}
}  // namespace detail

template <typename XnentList>
const DynamicXnentMask& GetXnentMask(XnentList l) {
  return detail::GetXnentMaskImpl(l);
}

template <std::size_t max_comp>
using StaticXnentMask = std::bitset<max_comp>;

template <std::size_t max_comp>
StaticXnentMask<max_comp> ToStatic(const DynamicXnentMask& mask) noexcept {
  auto r = StaticXnentMask<max_comp>{};
  std::copy(mask.Data(), mask.Data() + mask.SizeInBytes(),
            reinterpret_cast<std::uint8_t*>(&r));
  return r;
}

template <std::size_t max_comp>
bool operator==(const DynamicXnentMask& mask,
                const StaticXnentMask<max_comp>& smask) noexcept {
  return ToStatic<max_comp>(mask) == smask;
}

template <std::size_t max_comp>
bool operator==(const StaticXnentMask<max_comp>& smask,
                const DynamicXnentMask& mask) noexcept {
  return mask == smask;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator&(
    const DynamicXnentMask& mask,
    const StaticXnentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r &= smask;
  return r;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator&(const StaticXnentMask<max_comp>& smask,
                                    const DynamicXnentMask& mask) noexcept {
  return mask & smask;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator|(
    const DynamicXnentMask& mask,
    const StaticXnentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r |= smask;
  return r;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator|(const StaticXnentMask<max_comp>& smask,
                                    const DynamicXnentMask& mask) noexcept {
  return mask | smask;
}

}  // namespace internal
}  // namespace einu