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
#include <tuple>

namespace einu {
namespace tmp {

template <typename... Ts>
struct TypeList {};

template <typename TypeList>
struct Size;

template <typename... Ts>
struct Size<TypeList<Ts...>> {
  static constexpr std::size_t value = sizeof...(Ts);
};

template <typename TypeList, std::size_t index>
struct TypeAt;

template <typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0> {
  using Type = Head;
};

template <std::size_t index, typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, index> {
  static_assert(index < Size<TypeList<Head, Tail...>>::value &&
                "index out of bound");
  using Type = typename TypeAt<TypeList<Tail...>, index - 1>::Type;
};

template <typename TypeList, typename T>
struct IndexOf;
template <typename T, typename... Rest>
struct IndexOf<TypeList<T, Rest...>, T> {
  static constexpr std::size_t value = 0;
};
template <typename T, typename Head, typename... Rest>
struct IndexOf<TypeList<Head, Rest...>, T> {
  static constexpr std::size_t value = IndexOf<TypeList<Rest...>, T>::value + 1;
};

template <typename... TypeLists>
struct Concatenate;
template <typename TypeList>
struct Concatenate<TypeList> {
  using Type = TypeList;
};
template <typename Head, typename... Rest>
struct Concatenate<Head, Rest...> {
  using Type =
      typename Concatenate<Head, typename Concatenate<Rest...>::Type>::Type;
};

template <typename TypeList, typename T>
struct Append;
template <typename T, typename... Ts>
struct Append<TypeList<Ts...>, T> {
  using Type = TypeList<Ts..., T>;
};

template <typename TypeList, typename T>
struct Erase;
template <typename T, typename... Rest>
struct Erase<TypeList<T, Rest...>, T> {
  using Type = TypeList<Rest...>;
};
template <typename T, typename Head, typename... Rest>
struct Erase<TypeList<Head, Rest...>, T> {
  using Type =
      typename Concatenate<TypeList<Head>,
                           typename Erase<TypeList<Rest...>, T>::Type>::Type;
};

template <typename TypeList, typename T>
struct EraseAll;
template <typename T>
struct EraseAll<TypeList<T>, T> {
  using Type = TypeList<>;
};
template <typename T, typename Tail>
struct EraseAll<TypeList<Tail>, T> {
  using Type = TypeList<Tail>;
};
template <typename T, typename... Rest>
struct EraseAll<TypeList<T, Rest...>, T> {
  using Type = typename EraseAll<TypeList<Rest...>, T>::Type;
};
template <typename T, typename Head, typename... Rest>
struct EraseAll<TypeList<Head, Rest...>, T> {
  using Type =
      typename Concatenate<TypeList<Head>,
                           typename EraseAll<TypeList<Rest...>, T>::Type>::Type;
};

template <typename TypeList, typename T>
struct CountType;
template <typename T>
struct CountType<TypeList<>, T> {
  static constexpr std::size_t value = 0;
};
template <typename T, typename... Tail>
struct CountType<TypeList<T, Tail...>, T> {
  static constexpr std::size_t value =
      1 + CountType<TypeList<Tail...>, T>::value;
};
template <typename T, typename Head, typename... Tail>
struct CountType<TypeList<Head, Tail...>, T> {
  static constexpr std::size_t value = CountType<TypeList<Tail...>, T>::value;
};

}  // namespace tmp
}  // namespace einu
