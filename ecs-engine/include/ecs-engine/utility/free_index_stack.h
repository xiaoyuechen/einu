#pragma once

#include <cassert>
#include <mutex>
#include <vector>

#include "ecs-engine/utility/algorithm.h"

namespace ecs {

template <typename IndexType>
class FreeIndexStack {
 public:
  FreeIndexStack(IndexType count) {
    stack_.reserve(count);
    algo::Repeat(count, [&] { stack_.push_back(--count); });
  }

  IndexType Acquire() {
    auto value = stack_.back();
    stack_.pop_back();
    return value;
  }

  void Recall(IndexType value) { stack_.push_back(value); }

  IndexType Size() const noexcept { return stack_.size(); }

 private:
  std::vector<IndexType> stack_;
};

}  // namespace ecs
