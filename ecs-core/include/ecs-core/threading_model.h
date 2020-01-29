#ifndef THREADING_MODEL_H_
#define THREADING_MODEL_H_

#include <mutex>

namespace ecs {

class SingleThreaded {
 public:
  constexpr SingleThreaded() noexcept;

  class Lock {
   public:
    constexpr explicit Lock(SingleThreaded&) noexcept;
  };
};

class MultiThreaded {
 public:
  class Lock {
   public:
    explicit Lock(MultiThreaded& host);
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;

    ~Lock();

   private:
    MultiThreaded& host_;
  };

 private:
  std::mutex mutex_;
};

//////////////////////////////////////////////////////////////////////////

inline constexpr SingleThreaded::SingleThreaded() noexcept {}

inline constexpr SingleThreaded::Lock::Lock(SingleThreaded&) noexcept {}

inline MultiThreaded::Lock::Lock(MultiThreaded& host)
    : host_(host) {
  host_.mutex_.lock();
}

inline MultiThreaded::Lock::~Lock() { host_.mutex_.unlock(); }

}  // namespace ecs

#endif  // THREADING_MODEL_H_
