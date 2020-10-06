#pragma once

#include <vector>

#include "einu-core/i_entity.h"

namespace einu {

class EntityBuffer {
 public:
  void push_back(IEntity& ett) { buffer_.push_back(ett); }
  void clear() { buffer_.clear(); }
  auto begin() { return buffer_.begin(); }
  auto begin() const { return buffer_.begin(); }
  auto end() { return buffer_.end(); }
  auto end() const { return buffer_.end(); }

 private:
  using Buffer = std::vector<std::reference_wrapper<IEntity>>;
  Buffer buffer_;
};

}  // namespace einu