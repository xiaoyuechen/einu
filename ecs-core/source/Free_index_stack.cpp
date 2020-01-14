#include "ecs-core/object-pool/Free_index_stack.h"
#include <algorithm>
#include <cassert>
#include "ecs-core/utilities/algorithm.h"

namespace ecs {
Free_index_stack::Free_index_stack(size_type count)
{
  stack_.reserve(count);
  algo::repeat(count, [&] { stack_.push_back(--count); });
}

typename Free_index_stack::value_type Free_index_stack::aquire() noexcept
{
  assert(!stack_.empty() && "no index is free");
  auto value = stack_.back();
  auto lock = std::scoped_lock(mutex_);
  stack_.pop_back();
  return value;
}

void Free_index_stack::recall(value_type value)
{
  assert(std::find(std::begin(stack_), std::end(stack_), value) ==
             std::end(stack_) &&
         "the recalling value exists in stack");
  auto lock = std::scoped_lock(mutex_);
  stack_.push_back(value);
}

}  // namespace ecs