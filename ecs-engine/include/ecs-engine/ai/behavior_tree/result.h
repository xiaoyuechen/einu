#pragma once

#include <map>
#include <vector>

#include "ecs-engine/core/entity_id.h"

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
  using EIDs = std::vector<EntityID>;
  using Map = std::map<Status, EIDs>;
  using iterator = Map::iterator;
  using const_iterator = Map::const_iterator;

  Result();
  EIDs& operator[](const Status& status);
  EIDs& at(const Status& status);
  const EIDs& at(const Status& status) const;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  void clear() noexcept;

 private:
  Map map_;
};

//////////////////////////////////////////////////////////////////////////

inline Result::Result() {
  map_[Status::SUCCESS];
  map_[Status::FAILURE];
  map_[Status::RUNNING];
}

inline Result::EIDs& Result::operator[](const Status& status) {
  return map_[status];
}

inline Result::EIDs& Result::at(const Status& status) {
  return map_.at(status);
}

inline const Result::EIDs& Result::at(const Status& status) const {
  return map_.at(status);
}

inline Result::iterator Result::begin() noexcept { return map_.begin(); }
inline Result::const_iterator Result::begin() const noexcept {
  return map_.begin();
}
inline Result::iterator Result::end() noexcept { return map_.end(); }
inline Result::const_iterator Result::end() const noexcept {
  return map_.end();
}

inline void Result::clear() noexcept {
  for (auto& pair : map_) {
    pair.second.clear();
  }
}

}  // namespace bt
}  // namespace ai
}  // namespace ecs