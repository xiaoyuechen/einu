#include "ecs-core/object-pool/free_index_stack.h"

#include <algorithm>
#include <cassert>

#include "ecs-core/utility/algorithm.h"

namespace ecs {

FreeIndexStack::FreeIndexStack(std::size_t count) {
  stack_.reserve(count);
  algo::repeat(count, [&] { stack_.push_back(--count); });
}

typename std::size_t FreeIndexStack::Aquire() noexcept {
  assert(!stack_.empty() && "no index is free");
  auto lock = std::scoped_lock(mutex_);
  auto value = stack_.back();
  stack_.pop_back();
  return value;
}

void FreeIndexStack::Recall(std::size_t value) {
  assert(std::find(std::begin(stack_), std::end(stack_), value) ==
             std::end(stack_) &&
         "the recalling value exists in stack");
  auto lock = std::scoped_lock(mutex_);
  stack_.push_back(value);
}

}  // namespace ecs