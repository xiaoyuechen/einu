#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>

#include "ecs-engine/math/glm.h"

namespace ecs {

template <typename T = std::uint8_t, std::size_t channel_count = 4>
class Color {
 public:
  static constexpr std::size_t kChannelCount = channel_count;
  using ValueType = T;
  using InitializerList = std::initializer_list<T>;
  using Storage = glm::vec<channel_count, T>;

  Color() noexcept {}
  Color(InitializerList il) { std::copy(il.begin(), il.end(), &storage_[0]); }
  Color(const Storage& storage)
      : storage_(storage) {}

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

}  // namespace ecs