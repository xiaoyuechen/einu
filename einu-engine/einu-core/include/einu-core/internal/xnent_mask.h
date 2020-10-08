#pragma once

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <memory>
#include <vector>

#include "einu-core/internal/xnent_index.h"
#include "einu-core/xnent_list.h"

namespace einu {
namespace internal {

class XnentMask {
 public:
  using size_type = std::size_t;

  template <typename... Ts>
  explicit XnentMask(XnentList<Ts...>) {
    using namespace std;
    auto max_idx =
        max({XnentIndex::IndexType(internal::GetXnentIndex<Ts>())...});
    size_ = (max_idx + 8) / 8;
    data_ = std::make_unique<uint8_t[]>(size_);
    ((*(data_.get() + internal::GetXnentIndex<Ts>() / 8) |=
      uint8_t{1} << (internal::GetXnentIndex<Ts>() % 8)),
     ...);
  }

  const std::uint8_t* Data() const noexcept { return data_.get(); }
  size_type SizeInBytes() const noexcept { return size_; }

 private:
  std::unique_ptr<std::uint8_t[]> data_;
  std::size_t size_;
};

template <typename... Ts>
const XnentMask& GetXnentMask(XnentList<Ts...> l) {
  static auto& r = *new XnentMask(l);
  return r;
}

template <std::size_t max_comp>
using StaticXnentMask = std::bitset<max_comp>;

template <std::size_t max_comp>
StaticXnentMask<max_comp> ToStatic(const XnentMask& mask) noexcept {
  auto r = StaticXnentMask<max_comp>{};
  std::copy(mask.Data(), mask.Data() + mask.SizeInBytes(), &r);
  return r;
}

template <std::size_t max_comp>
bool operator==(const XnentMask& mask,
                const StaticXnentMask<max_comp>& smask) noexcept {
  return ToStatic<max_comp>(mask) == smask;
}

template <std::size_t max_comp>
bool operator==(const StaticXnentMask<max_comp>& smask,
                const XnentMask& mask) noexcept {
  return mask == smask;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator&(
    const XnentMask& mask, const StaticXnentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r &= smask;
  return r;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator&(const StaticXnentMask<max_comp>& smask,
                                    const XnentMask& mask) noexcept {
  return mask & smask;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator|(
    const XnentMask& mask, const StaticXnentMask<max_comp>& smask) noexcept {
  auto r = ToStatic<max_comp>(mask);
  r |= smask;
  return r;
}

template <std::size_t max_comp>
StaticXnentMask<max_comp> operator|(const StaticXnentMask<max_comp>& smask,
                                    const XnentMask& mask) noexcept {
  return mask | smask;
}

}  // namespace internal
}  // namespace einu