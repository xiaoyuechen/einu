#pragma once
#include <vector>
#include <mutex>

namespace ecs {
class Free_index_stack {
 public:
  using value_type = std::size_t;
  using size_type = std::size_t;

 public:
  Free_index_stack(size_type count);
  value_type aquire() noexcept;
  void recall(value_type value);
  size_type size() const noexcept;

 private:
  std::vector<value_type> stack_;
  std::mutex mutex_;
};

inline typename Free_index_stack::size_type Free_index_stack::size() const
    noexcept
{
  return stack_.size();
}
}  // namespace ecs
