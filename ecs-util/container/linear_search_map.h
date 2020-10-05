#pragma once

#include <algorithm>
#include <vector>

namespace einu {
template <typename Key, typename T,
          template <typename> typename UnderlyingContainer = std::vector>
class LinearSearchMap {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using Underlying = UnderlyingContainer<value_type>;
  using size_type = typename Underlying::size_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename Underlying::pointer;
  using const_pointer = typename Underlying::const_pointer;
  using iterator = typename Underlying::iterator;
  using const_iterator = typename Underlying::const_iterator;
  using reverse_iterator = typename Underlying::reverse_iterator;
  using const_reverse_iterator = typename Underlying::const_reverse_iterator;

  // Iterators
  iterator begin() noexcept { return underlying_.begin(); }
  const_iterator begin() const noexcept { return underlying_.begin(); }
  const_iterator cbegin() const noexcept { return underlying_.cbegin(); }

  iterator end() noexcept { return underlying_.end(); }
  const_iterator end() const noexcept { return underlying_.end(); }
  const_iterator cend() const noexcept { return underlying_.cend(); }

  // Capacity
  [[nodiscard]] bool empty() const noexcept { return underlying_.empty(); }
  size_type size() const noexcept { return underlying_.size(); }
  size_type max_size() const noexcept { return underlying_.max_size(); }

  // Modifiers
  void clear() noexcept { underlying_.clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto it = find(value.first);
    if (it == end()) {
      it = underlying_.insert(end(), value);
      return std::make_pair(it, true);
    }
    return std::make_pair(it, false);
  }

  std::pair<iterator, bool> insert(value_type&& value) {
    auto it = find(value.first);
    if (it == end()) {
      it = underlying_.insert(end(), std::move(value));
      return std::make_pair(it, true);
    }
    return std::make_pair(it, false);
  }

  void erase(const key_type& key) {
    auto it = find(key);
    underlying_.erase(it);
  }

  // Lookup
  T& at(const Key& key) { return find(key)->second; }
  const T& at(const Key& key) const { return find(key)->second; }
  T& operator[](const Key& key) {
    auto it = find(key);
    if (it == underlying_.end()) {
      underlying_.emplace_back();
      underlying_.back().first = key;
      return underlying_.back().second;
    }
    return it->second;
  }

  iterator find(const Key& key) {
    return std::find_if(underlying_.begin(), underlying_.end(),
                        [&](const auto& pair) { return pair.first == key; });
  }

  const_iterator find(const Key& key) const {
    return std::find_if(underlying_.begin(), underlying_.end(),
                        [&](const auto& pair) { return pair.first == key; });
  }

 private:
  Underlying underlying_;
};
}  // namespace einu
