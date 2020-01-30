#pragma once
#include <vector>

namespace ecs {
namespace patt {
class I_observer;
class I_subject {
 public:
  void add_to_broadcast_list(I_observer& obs);
  void remove_from_broadcast_list(const I_observer& obs) noexcept;
  void broadcast();

 private:
  std::vector<I_observer*> observer_arr_;
};

class I_observer {
 public:
  void subscribe(I_subject& sbj);
  void unsubscribe(I_subject& sbj);
  virtual void observe(I_subject& sbj) = 0;

  private:
  std::vector<I_subject*> subject_arr_;
};
}  // namespace patt
}  // namespace ecs