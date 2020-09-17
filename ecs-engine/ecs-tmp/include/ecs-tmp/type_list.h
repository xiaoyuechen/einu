#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace ecs {
namespace tmp {

template <typename... Ts>
struct TypeList {};

template <typename Base, typename... Subs>
struct SubtypeList : public tmp::TypeList<Subs...> {
  static_assert((std::is_base_of<Base, Subs>::value && ...),
                "<Base> must be the base class of all the <Subs>");
};

template <typename TypeList>
struct Size;
template <typename... Ts>
struct Size<TypeList<Ts...>> {
  static constexpr std::size_t value = sizeof...(Ts);
};

template <typename TypeList, std::size_t index>
struct TypeAt;
template <std::size_t index, typename... Ts>
struct TypeAt<TypeList<Ts...>, index> {
  static_assert(index < Size<TypeList<Ts...>>::value && "index out of bound");
  using Type = typename std::tuple_element<index, std::tuple<Ts...>>::type;
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

}  // namespace tmp
}  // namespace ecs
