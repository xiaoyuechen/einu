#pragma once

namespace einu {
namespace tmp {

namespace internal {
template <typename Predicate, std::size_t... Is>
constexpr void StaticForImpl(Predicate&& pred, std::index_sequence<Is...>) {
  (pred(std::integral_constant<std::size_t, Is>{}), ...);
}
}  // namespace internal

template <std::size_t count, typename Predicate>
constexpr void StaticFor(Predicate&& pred) {
  internal::StaticForImpl(std::forward<Predicate>(pred),
                          std::make_index_sequence<count>{});
}

}  // namespace tmp
}  // namespace einu