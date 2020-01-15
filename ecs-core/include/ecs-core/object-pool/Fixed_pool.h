#pragma once
#include <cassert>
#include <functional>
#include <vector>
#include "Free_index_stack.h"
#include "ecs-core/utility/algorithm.h"

namespace ecs {
template <typename T, typename Allocator = std::allocator<T>>
class Fixed_pool {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const pointer;

 public:
  explicit Fixed_pool(size_type count, const Allocator& alloc = Allocator());
  Fixed_pool(size_type count,
             const T& value,
             const Allocator& alloc = Allocator());
  template <typename... Args>
  Fixed_pool(size_type count,
             std::tuple<Args&&...> args_tup,
             const Allocator& alloc = Allocator());

  Fixed_pool(const Fixed_pool&) = delete;
  Fixed_pool& operator=(const Fixed_pool&) = delete;

  size_type size() const noexcept;
  size_type free_size() const noexcept;

  [[nodiscard]] reference aquire();
  void recall(const_reference obj);

 private:
  Free_index_stack free_index_stack_;
  std::vector<T, Allocator> object_arr_;
};
}  // namespace ecs

namespace ecs {
template <typename T, typename Allocator>
inline Fixed_pool<T, Allocator>::Fixed_pool(size_type count,
                                            const Allocator& alloc)
    : object_arr_(count, alloc)
    , free_index_stack_(count) {}

template <typename T, typename Allocator>
inline Fixed_pool<T, Allocator>::Fixed_pool(size_type count,
                                            const T& value,
                                            const Allocator& alloc)
    : object_arr_(count, value, alloc)
    , free_index_stack_(count) {}

template <typename T, typename Allocator>
template <typename... Args>
inline Fixed_pool<T, Allocator>::Fixed_pool(size_type count,
                                            std::tuple<Args&&...> args_tup,
                                            const Allocator& alloc)
    : object_arr_(alloc)
    , free_index_stack_(count) {
  auto init_object_arr = [&, count](Args&&... args) {
    algo::repeat(
        count, [&] { object_arr_.emplace_back(std::forward<Args>(args)...); });
  };
  algo::apply(init_object_arr, args_tup);
}

template <typename T, typename Allocator>
inline typename Fixed_pool<T, Allocator>::size_type
Fixed_pool<T, Allocator>::size() const noexcept {
  return object_arr_.size();
}

template <typename T, typename Allocator>
inline typename Fixed_pool<T, Allocator>::size_type
Fixed_pool<T, Allocator>::free_size() const noexcept {
  return free_index_stack_.size();
}

template <typename T, typename Allocator>
inline typename Fixed_pool<T, Allocator>::reference
Fixed_pool<T, Allocator>::aquire() {
  return object_arr_[free_index_stack_.aquire()];
}

template <typename T, typename Allocator>
inline void Fixed_pool<T, Allocator>::recall(const_reference obj) {
  auto index = &obj - object_arr_.data();
  free_index_stack_.recall(index);
}
}  // namespace ecs