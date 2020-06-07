#pragma once

#include <tuple>

namespace ecs {

template <typename... Itrs>
class ZipIterator {
 public:
  ZipIterator(Itrs... itrs)
      : itrs_(itrs...) {}

  ZipIterator& operator++() {
    (++std::get<Itrs>(itrs_), ...);
    return *this;
  }

  ZipIterator operator++(int) {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  bool operator==(ZipIterator other) const {
    return ((std::get<Itrs>(itrs_) == std::get<Itrs>(other.itrs_)) && ...);
  }

  bool operator!=(ZipIterator other) const { return !(*this == other); }

  auto operator*() { return std::forward_as_tuple(*std::get<Itrs>(itrs_)...); }

 private:
  using ItrTup = std::tuple<Itrs...>;

  ItrTup itrs_;
};

template <typename... Containers>
class Zip {
 public:
  Zip(Containers&... containers)
      : containers_(containers...) {}

  auto begin() {
    return ZipIterator(std::get<Containers&>(containers_).begin()...);
  }
  auto begin() const {
    return ZipIterator(std::get<Containers&>(containers_).begin()...);
  }

  auto end() {
    return ZipIterator(std::get<Containers&>(containers_).end()...);
  }
  auto end() const {
    return ZipIterator(std::get<Containers&>(containers_).end()...);
  }

 private:
  using ContainerTup = std::tuple<Containers&...>;
  ContainerTup containers_;
};

}  // namespace ecs