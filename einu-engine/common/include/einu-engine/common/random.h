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

#include <random>

namespace einu {

namespace internal {

inline std::random_device& GetRandomDevice() {
  static std::random_device device{};
  return device;
}

inline std::mt19937& GetGenerator() {
  static std::random_device device{};
  static std::mt19937 generator{GetRandomDevice()()};
  return generator;
}

}  // namespace internal

template <typename T>
T RandomUniform(const T min, const T max) {
  std::uniform_real_distribution<T> distribution(min, max);
  return distribution(internal::GetGenerator());
}

}  // namespace einu
