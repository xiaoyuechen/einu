#pragma once

#include <algorithm>
#include <array>
#include <bitset>

namespace einu {

template <typename T, std::size_t N>
class CircularBuffer {
 public:
  using Buffer = std::array<T, N>;

  void AdvanceCursor() noexcept { cursor = (cursor + 1) % N; }

  void SetCurrent(T val) noexcept { buffer_[cursor] = val; }

  T GetCurrent() const noexcept { return buffer_[cursor]; }

  const Buffer& GetSortedBuffer() const noexcept {
    cache_ = buffer_;
    std::rotate(cache_.begin(), cache_.begin() + cursor + 1, cache_.end());
    return cache_;
  }

 private:
  std::size_t cursor = 0;
  Buffer buffer_;
  mutable Buffer cache_;
};

template <std::size_t N>
class CircularBuffer<bool, N> {
 public:
  using Buffer = std::bitset<N>;

  void AdvanceCursor() noexcept { cursor = (cursor + 1) % N; }

  void SetCurrent(bool val) noexcept { buffer_[cursor] = val; }

  bool GetCurrent() const noexcept { return buffer_.[cursor]; }

  const Buffer& GetSortedBuffer() const noexcept {
    cache_ = (buffer_ << (cursor + 1)) | (buffer_ >> (N - cursor - 1));
    return cache_;
  }

 private:
  std::size_t cursor = 0;
  Buffer buffer_;
  mutable Buffer cache_;
};

}  // namespace einu
