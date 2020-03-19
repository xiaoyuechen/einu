#pragma once

#include <algorithm>
#include <tuple>
#include <utility>

namespace ecs {

namespace algo {

template <typename Size, typename Predicate>
constexpr void Repeat(Size count, Predicate&& pred);

template <typename F, typename Tuple>
constexpr auto Apply(F&& f, Tuple&& t);

template <typename Container, typename T, typename ForwardIterator>
constexpr void EraseRemove(Container&& c,
                           ForwardIterator first,
                           ForwardIterator last,
                           const T& val);

template <std::size_t count, typename Predicate>
constexpr void StaticFor(Predicate&& pred);

//////////////////////////////////////////////////////////////////////////

template <typename Size, typename Predicate>
constexpr void Repeat(Size count, Predicate&& pred) {
  while (count--) pred();
}

namespace detail {
template <typename F, typename Tuple, std::size_t... I>
constexpr auto ApplyImpl(F&& f, Tuple&& t, std::index_sequence<I...>) {
  return std::invoke(std::forward<F>(f),
                     std::move(std::get<I>(std::forward<Tuple>(t))...));
}
}  // namespace detail

template <typename F, typename Tuple>
constexpr auto Apply(F&& f, Tuple&& t) {
  return detail::ApplyImpl(
      std::forward<F>(f),
      std::forward<Tuple>(t),
      std::make_index_sequence<
          std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

template <typename Container, typename T, typename ForwardIterator>
constexpr void EraseRemove(Container&& c,
                           ForwardIterator first,
                           ForwardIterator last,
                           const T& val) {
  c.erase(std::remove(first, last, val), last);
}

namespace detail {
template <typename Predicate, std::size_t... Is>
constexpr void StaticForImpl(Predicate&& pred, std::index_sequence<Is...>) {
  (pred(std::integral_constant<std::size_t, Is>{}), ...);
}
}  // namespace detail

template <std::size_t count, typename Predicate>
constexpr void StaticFor(Predicate&& pred) {
  detail::StaticForImpl(std::forward<Predicate>(pred),
                        std::make_index_sequence<count>{});
}

}  // namespace algo

}  // namespace ecs

