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

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_BitScanReverse)
#if _WIN64
#pragma intrinsic(_BitScanReverse64)
#endif
#endif

namespace einu {
namespace util {

int CountLeftZero(std::uint32_t x) noexcept;
std::optional<int> CountLeftZero(const std::uint32_t* begin,
                                 const std::uint32_t* end) noexcept;

int CountLeftZero(std::uint64_t x) noexcept;
std::optional<int> CountLeftZero(const std::uint64_t* begin,
                                 const std::uint64_t* end) noexcept;

// TODO(Xiaoyue Chen): This is extremely slow. Use architecture specific ffs
// instruction instead.
// std::size_t FindFirstSet(std::vector<bool>::const_iterator begin,
//                         std::vector<bool>::const_iterator end) noexcept {
//  auto it = std::find(begin, end, true);
//  return std::distance(begin, it);
//}

// TODO(Xiaoyue Chen): This is a temporary solution. It uses more memory. We
// need to support an actual bit array.
inline std::size_t FindFirstSet(
    std::vector<std::uint8_t>::const_iterator begin,
    std::vector<std::uint8_t>::const_iterator end) noexcept {
  auto it = std::find(begin, end, true);
  return std::distance(begin, it);
}

namespace internal {

template <typename Mask>
std::optional<int> CountLeftZero(Mask* begin, Mask* end) noexcept {
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter != 0) {
      return 8 * sizeof(Mask) * (iter - begin) +
             ::einu::util::CountLeftZero(*iter);
    }
  }
  return std::nullopt;
}

}  // namespace internal

inline int CountLeftZero(std::uint32_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanReverse(&index, x);
  return 31 ^ static_cast<int>(index);
#else
  return __builtin_clz(x);
#endif
}

inline std::optional<int> CountLeftZero(const std::uint32_t* begin,
                                        const std::uint32_t* end) noexcept {
  return internal::CountLeftZero(begin, end);
}

#if _WIN64 || __x86_64__ || __ppc64__

inline int CountLeftZero(std::uint64_t x) noexcept {
#ifdef _MSC_VER
  unsigned long index;  // NOLINT
  _BitScanReverse64(&index, x);
  return 63 ^ static_cast<int>(index);
#else
  return __builtin_clzll(x);
#endif
}

inline std::optional<int> CountLeftZero(const std::uint64_t* begin,
                                        const std::uint64_t* end) noexcept {
  return internal::CountLeftZero(begin, end);
}

#endif

class BitVector {
 public:
  using size_type = std::size_t;
  static constexpr const std::size_t kWordBits = sizeof(size_type) * 8;

  explicit BitVector(size_type count = 0, bool value = false)
      : mask_(BitToWordCount(count), value ? ~0 : 0), size_{count} {}

  size_type size() const noexcept { return size_; }

  std::optional<int> countl_zero() const noexcept {
    auto clz = CountLeftZero(mask_.data(), mask_.data() + mask_.size());
    if (clz.has_value() && clz <= size_) {
      return clz;
    }
    return std::nullopt;
  }

  bool test(size_type pos) const noexcept {
    auto bit_mask = GetBitMask(pos);
    return (mask_[pos / kWordBits] & bit_mask) == bit_mask;
  }

  void set(size_type pos) noexcept {
    mask_[pos / kWordBits] |= GetBitMask(pos);
  }

  void reset(size_type pos) noexcept {
    mask_[pos / kWordBits] &= ~GetBitMask(pos);
  }

  void resize(size_type count, bool value = false) {
    if (size_ < count) {
      auto bit_vec = BitVector{count, value};
      std::copy(mask_.begin(), mask_.end(), bit_vec.mask_.begin());
      auto end_mask = ~size_type(0);
      end_mask >>= (size_ % kWordBits);
      if (value)
        bit_vec.mask_[size_ / kWordBits] |= end_mask;
      else
        bit_vec.mask_[size_ / kWordBits] &= ~end_mask;
      *this = std::move(bit_vec);
    } else if (size_ > count) {
      size_ = count;
      mask_.resize(BitToWordCount(count));
    }
  }

 private:
  constexpr size_type GetBitMask(size_type pos) const noexcept {
    return (~(~size_type(0) >> 1) >> (pos % kWordBits));
  }

  constexpr size_type BitToWordCount(size_type count) const noexcept {
    return (count + kWordBits - 1) / kWordBits;
  }

  std::vector<size_type> mask_;
  size_type size_;
};

}  // namespace util
}  // namespace einu
