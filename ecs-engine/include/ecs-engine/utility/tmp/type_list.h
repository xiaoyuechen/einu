#pragma once

#include <cstddef>
#include <tuple>

namespace ecs {
namespace tmp {

template <typename... Ts>
struct TypeList;

template <typename TypeList>
struct Size;

template <typename TypeList, std::size_t index>
struct TypeAt;

template <typename TypeList, typename T>
struct IndexOf;

template <typename... TypeLists>
struct Concatenate;

template <typename TypeList, typename T>
struct Append;

template <typename TypeList, typename T>
struct Erase;

template <typename TypeList, typename T>
struct EraseAll;

template <typename TypeList>
struct TupleOf;

template <typename TypeList>
struct TupleRefOf;

template <typename TypeList>
struct TuplePtrOf;

template <template <typename... Args> typename Wrapper, typename TypeList>
struct TupleWrapperOf;

template <template <typename... Args> typename Wrapper, typename TypeList>
struct ListWrapperOf;

//////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct TypeList {};

template <typename... Ts>
struct Size<TypeList<Ts...>> {
  static constexpr std::size_t value = sizeof...(Ts);
};

template <std::size_t index, typename... Ts>
struct TypeAt<TypeList<Ts...>, index> {
  static_assert(index < Size<TypeList<Ts...>>::value && "index out of bound");
  using Type = typename std::tuple_element<index, std::tuple<Ts...>>::type;
};

template <typename TypeList>
struct Concatenate<TypeList> {
  using Result = TypeList;
};

template <typename... LhsTs, typename... RhsTs>
struct Concatenate<TypeList<LhsTs...>, TypeList<RhsTs...>> {
  using Result = TypeList<LhsTs..., RhsTs...>;
};

template <typename Head, typename... Rest>
struct Concatenate<Head, Rest...> {
  using Result =
      typename Concatenate<Head, typename Concatenate<Rest...>::Result>::Result;
};

template <typename T, typename... Rest>
struct IndexOf<TypeList<T, Rest...>, T> {
  static constexpr std::size_t value = 0;
};

template <typename T, typename Head, typename... Rest>
struct IndexOf<TypeList<Head, Rest...>, T> {
  static constexpr std::size_t value = IndexOf<TypeList<Rest...>, T>::value + 1;
};

template <typename T, typename... Ts>
struct Append<TypeList<Ts...>, T> {
  using Result = TypeList<Ts..., T>;
};

template <typename T, typename... Rest>
struct Erase<TypeList<T, Rest...>, T> {
  using Result = TypeList<Rest...>;
};

template <typename T, typename Head, typename... Rest>
struct Erase<TypeList<Head, Rest...>, T> {
  using Result = typename Concatenate<
      TypeList<Head>, typename Erase<TypeList<Rest...>, T>::Result>::Result;
};

template <typename T>
struct EraseAll<TypeList<T>, T> {
  using Result = TypeList<>;
};

template <typename T, typename Tail>
struct EraseAll<TypeList<Tail>, T> {
  using Result = TypeList<Tail>;
};

template <typename T, typename... Rest>
struct EraseAll<TypeList<T, Rest...>, T> {
  using Result = typename EraseAll<TypeList<Rest...>, T>::Result;
};

template <typename T, typename Head, typename... Rest>
struct EraseAll<TypeList<Head, Rest...>, T> {
  using Result = typename Concatenate<
      TypeList<Head>, typename EraseAll<TypeList<Rest...>, T>::Result>::Result;
};

template <typename... Ts>
struct TupleOf<TypeList<Ts...>> {
  using Type = std::tuple<Ts...>;
};

template <typename... Ts>
struct TupleRefOf<TypeList<Ts...>> {
  using Type = std::tuple<Ts&...>;
};

template <typename... Ts>
struct TuplePtrOf<TypeList<Ts...>> {
  using Type = std::tuple<Ts*...>;
};

template <template <typename... Args> typename Wrapper, typename... Ts>
struct TupleWrapperOf<Wrapper, TypeList<Ts...>> {
  using Type = std::tuple<Wrapper<Ts>...>;
};

template <template <typename... Args> typename Wrapper, typename... Ts>
struct ListWrapperOf<Wrapper, TypeList<Ts...>> {
  using Type = TypeList<Wrapper<Ts>...>;
};

}  // namespace tmp
}  // namespace ecs
