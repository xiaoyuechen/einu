#include "ecs-core/utility/pattern.h"

#include <algorithm>

namespace ecs {

namespace patt {

void I_subject::add_to_broadcast_list(I_observer& obs) {
  observer_arr_.push_back(&obs);
}

void I_subject::remove_from_broadcast_list(const I_observer& obs) noexcept {
  auto new_end =
      std::remove(std::begin(observer_arr_), std::end(observer_arr_), &obs);
  observer_arr_.erase(new_end, std::end(observer_arr_));
}

void I_subject::broadcast() {
  for_each(std::begin(observer_arr_), std::end(observer_arr_), [=](auto&& obs) {
    obs->observe(*this);
  });
}

void I_observer::subscribe(I_subject& sbj) {
  subject_arr_.push_back(&sbj);
  sbj.add_to_broadcast_list(*this);
}

void I_observer::unsubscribe(I_subject& sbj) {
  auto new_end =
      std::remove(std::begin(subject_arr_), std::end(subject_arr_), &sbj);
  subject_arr_.erase(new_end, std::end(subject_arr_));
  sbj.remove_from_broadcast_list(*this);
}

}  // namespace patt

}  // namespace ecs