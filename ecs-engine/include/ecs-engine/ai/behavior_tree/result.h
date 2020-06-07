#pragma once

#include <map>
#include <vector>

#include "ecs-engine/core/entity_data.h"
#include "ecs-engine/core/entity_data_vector.h"

namespace ecs {
namespace ai {
namespace bt {

enum class Status {
  SUCCESS,
  FAILURE,
  RUNNING,
};

class Result {
 public:
  using Map = std::map<Status, EntityDataVector>;
  using iterator = Map::iterator;
  using const_iterator = Map::const_iterator;

  Result() {
    map_[Status::SUCCESS];
    map_[Status::FAILURE];
    map_[Status::RUNNING];
  }

  EntityDataVector& operator[](const Status& status) { return map_.at(status); }

  const EntityDataVector& operator[](const Status& status) const {
    return map_.at(status);
  }
  iterator begin() noexcept { return map_.begin(); }
  const_iterator begin() const noexcept { return map_.begin(); }
  iterator end() noexcept { return map_.end(); }
  const_iterator end() const noexcept { return map_.end(); }
  void clear() noexcept {
    for (auto& pair : map_) {
      pair.second.clear();
    }
  }

 private:
  Map map_;
};

}  // namespace bt
}  // namespace ai
}  // namespace ecs