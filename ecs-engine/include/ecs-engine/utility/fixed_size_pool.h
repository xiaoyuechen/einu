#pragma once

#include <functional>
#include <vector>

#include "ecs-engine/utility/algorithm.h"
#include "free_index_stack.h"

namespace ecs {

template <typename T, typename Allocator = std::allocator<T>>
class FixedSizePool {
 public:
  explicit FixedSizePool(std::size_t count,
                         const Allocator& alloc = Allocator())
      : object_arr_(count, alloc)
      , free_index_stack_(count) {}

  FixedSizePool(std::size_t count, const T& value,
                const Allocator& alloc = Allocator())
      : object_arr_(count, value, alloc)
      , free_index_stack_(count) {}

  template <typename... Args>
  FixedSizePool(std::size_t count, std::tuple<Args&&...> args_tup,
                const Allocator& alloc = Allocator())
      : object_arr_(alloc)
      , free_index_stack_(count) {
    auto init_object_arr = [&, count](Args&&... args) {
      algo::Repeat(count, [&] {
        object_arr_.emplace_back(std::forward<Args>(args)...);
      });
    };
    algo::Apply(init_object_arr, args_tup);
  }

  FixedSizePool(const FixedSizePool&) = delete;
  FixedSizePool& operator=(const FixedSizePool&) = delete;

  std::size_t Size() const noexcept { return object_arr_.size(); }
  std::size_t FreeSize() const noexcept { return free_index_stack_.Size(); }

  [[nodiscard]] T& Acquire() {
    return object_arr_[free_index_stack_.Acquire()];
  }

  void Recall(const T& obj) {
    auto index = &obj - object_arr_.data();
    free_index_stack_.Recall(index);
  }

 private:
  FreeIndexStack<std::size_t> free_index_stack_;
  std::vector<T, Allocator> object_arr_;
};

}  // namespace ecs