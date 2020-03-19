#pragma once

#include <cassert>
#include <mutex>
#include <vector>

#include "ecs-engine/utility/algorithm.h"

namespace ecs {

template <typename IndexType, typename ThreadingModel>
class FreeIndexStack : public ThreadingModel {
 public:
  FreeIndexStack(IndexType count);
  IndexType Acquire();
  void Recall(IndexType value);
  IndexType Size() const noexcept;

 private:
  std::vector<IndexType> stack_;
};

//////////////////////////////////////////////////////////////////////////

template <typename IndexType, typename ThreadingModel>
inline IndexType FreeIndexStack<IndexType, ThreadingModel>::Size() const
    noexcept {
  return stack_.size();
}

template <typename IndexType, typename ThreadingModel>
FreeIndexStack<IndexType, ThreadingModel>::FreeIndexStack(IndexType count) {
  stack_.reserve(count);
  algo::Repeat(count, [&] { stack_.push_back(--count); });
}

template <typename IndexType, typename ThreadingModel>
typename IndexType FreeIndexStack<IndexType, ThreadingModel>::Acquire() {
  assert(!stack_.empty() && "no index is free");
  typename ThreadingModel::Lock lock(*this);
  auto value = stack_.back();
  stack_.pop_back();
  return value;
}

template <typename IndexType, typename ThreadingModel>
void FreeIndexStack<IndexType, ThreadingModel>::Recall(IndexType value) {
  assert(std::find(std::begin(stack_), std::end(stack_), value) ==
             std::end(stack_) &&
         "the recalling value exists in stack");
  typename ThreadingModel::Lock lock(*this);
  stack_.push_back(value);
}

}  // namespace ecs

