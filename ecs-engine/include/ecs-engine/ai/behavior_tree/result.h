#pragma once

#include <map>
#include <vector>

#include "ecs-engine/core/entity.h"

namespace ecs {
namespace ai {
namespace bt {

enum class Status {
  kSuccess,
  kFailure,
  kRunning,
};

class Result {
 public:
  using EntitySet = std::vector<std::reference_wrapper<IEntity>>;
  using Map = std::map<Status, EntitySet>;
  using iterator = typename Map::iterator;
  using const_iterator = typename Map::const_iterator;

  Result() {
    map_[Status::kSuccess];
    map_[Status::kFailure];
    map_[Status::kRunning];
  }

  EntitySet& operator[](const Status& status) { return map_.at(status); }

  const EntitySet& operator[](const Status& status) const {
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