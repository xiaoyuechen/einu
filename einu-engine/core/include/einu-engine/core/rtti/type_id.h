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

#include <cstddef>
#include <type_traits>

namespace einu {
namespace rtti {

class TypeID {
 public:
  using IndexType = std::size_t;

  constexpr explicit TypeID(IndexType index = ~IndexType(0)) noexcept
      : index_(index) {}
  operator IndexType&() noexcept { return index_; }
  operator IndexType() const noexcept { return index_; }

 private:
  IndexType index_;
};

inline bool IsAssigned(TypeID id) noexcept { return id != TypeID(); }

namespace internal {

template <typename T>
struct TypeIDStorage {
  inline static TypeID value = TypeID();
};

}  // namespace internal

template <typename T>
void SetTypeID(TypeID id) noexcept {
  internal::TypeIDStorage<std::decay<T>::type>::value = id;
}

template <typename T>
TypeID GetTypeID() noexcept {
  return internal::TypeIDStorage<std::decay<T>::type>::value;
}

}  // namespace rtti
}  // namespace einu
