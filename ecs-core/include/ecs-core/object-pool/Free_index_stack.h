#ifndef FREE_INDEX_STACK_H_
#define FREE_INDEX_STACK_H_

#include <mutex>
#include <vector>

namespace ecs {

class FreeIndexStack {
 public:
  FreeIndexStack(std::size_t count);
  std::size_t Acquire() noexcept;
  void Recall(std::size_t value);
  std::size_t Size() const noexcept;

 private:
  std::vector<std::size_t> stack_;
  std::mutex mutex_;
};

inline std::size_t FreeIndexStack::Size() const noexcept {
  return stack_.size();
}

}  // namespace ecs

#endif  // FREE_INDEX_STACK_H_