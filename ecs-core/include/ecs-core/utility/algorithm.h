#pragma once
namespace ecs {
namespace algo {
template <typename Size, typename Predicate>
constexpr void repeat(Size count, Predicate&& pred);

template <typename F, typename Tuple>
constexpr auto apply(F&& f, Tuple&& t);
}  // namespace algo
}  // namespace ecs

namespace ecs {
namespace algo {
template <typename Size, typename Predicate>
constexpr void repeat(Size count, Predicate&& pred) {
  while (count--) pred();
}

namespace detail {
template <typename F, typename Tuple, std::size_t... I>
constexpr auto apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
  return std::invoke(std::forward<F>(f),
                     std::move(std::get<I>(std::forward<Tuple>(t))...));
}
}  // namespace detail

template <typename F, typename Tuple>
constexpr auto apply(F&& f, Tuple&& t) {
  return detail::apply_impl(
      std::forward<F>(f),
      std::forward<Tuple>(t),
      std::make_index_sequence<
          std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}
}  // namespace algo
}  // namespace ecs