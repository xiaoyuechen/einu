#ifndef FIXED_SIZE_POOL_H_
#define FIXED_SIZE_POOL_H_

#include <cassert>
#include <functional>
#include <vector>

#include "ecs-core/utility/algorithm.h"
#include "free_index_stack.h"

namespace ecs {

template <typename T,
          typename ThreadingModel,
          typename Allocator = std::allocator<T>>
class FixedSizePool {
 public:
  explicit FixedSizePool(std::size_t count,
                         const Allocator& alloc = Allocator());
  FixedSizePool(std::size_t count,
                const T& value,
                const Allocator& alloc = Allocator());
  template <typename... Args>
  FixedSizePool(std::size_t count,
                std::tuple<Args&&...> args_tup,
                const Allocator& alloc = Allocator());

  FixedSizePool(const FixedSizePool&) = delete;
  FixedSizePool& operator=(const FixedSizePool&) = delete;

  std::size_t Size() const noexcept;
  std::size_t FreeSize() const noexcept;

  [[nodiscard]] T& Acquire();
  void Recall(const T& obj);

 private:
  FreeIndexStack<std::size_t, ThreadingModel> free_index_stack_;
  std::vector<T, Allocator> object_arr_;
};

//////////////////////////////////////////////////////////////////////////

template <typename T, typename ThreadingModel, typename Allocator>
inline FixedSizePool<T, ThreadingModel, Allocator>::FixedSizePool(
    std::size_t count, const Allocator& alloc)
    : object_arr_(count, alloc)
    , free_index_stack_(count) {}

template <typename T, typename ThreadingModel, typename Allocator>
inline FixedSizePool<T, ThreadingModel, Allocator>::FixedSizePool(
    std::size_t count, const T& value, const Allocator& alloc)
    : object_arr_(count, value, alloc)
    , free_index_stack_(count) {}

template <typename T, typename ThreadingModel, typename Allocator>
template <typename... Args>
inline FixedSizePool<T, ThreadingModel, Allocator>::FixedSizePool(
    std::size_t count, std::tuple<Args&&...> args_tup, const Allocator& alloc)
    : object_arr_(alloc)
    , free_index_stack_(count) {
  auto init_object_arr = [&, count](Args&&... args) {
    algo::Repeat(
        count, [&] { object_arr_.emplace_back(std::forward<Args>(args)...); });
  };
  algo::Apply(init_object_arr, args_tup);
}

template <typename T, typename ThreadingModel, typename Allocator>
inline std::size_t FixedSizePool<T, ThreadingModel, Allocator>::Size() const
    noexcept {
  return object_arr_.size();
}

template <typename T, typename ThreadingModel, typename Allocator>
inline std::size_t FixedSizePool<T, ThreadingModel, Allocator>::FreeSize() const
    noexcept {
  return free_index_stack_.Size();
}

template <typename T, typename ThreadingModel, typename Allocator>
inline T& FixedSizePool<T, ThreadingModel, Allocator>::Acquire() {
  return object_arr_[free_index_stack_.Acquire()];
}

template <typename T, typename ThreadingModel, typename Allocator>
inline void FixedSizePool<T, ThreadingModel, Allocator>::Recall(const T& obj) {
  auto index = &obj - object_arr_.data();
  free_index_stack_.Recall(index);
}

}  // namespace ecs

#endif  // FIXED_SIZE_POOL_H_