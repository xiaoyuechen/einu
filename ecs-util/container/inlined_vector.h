#ifndef FIXED_SIZE_VECTOR_H_
#define FIXED_SIZE_VECTOR_H_

#include <algorithm>
#include <array>
#include <initializer_list>

namespace einu {

template <typename T, std::size_t N>
class InlinedVector {
  using Memory = std::array<T, N>;

 public:
  using value_type = typename Memory::value_type;
  using pointer = typename Memory::pointer;
  using const_pointer = typename Memory::const_pointer;
  using size_type = typename Memory::size_type;
  using difference_type = typename Memory::difference_type;
  using reference = typename Memory::reference;
  using const_reference = typename Memory::const_reference;
  using iterator = typename Memory::iterator;
  using const_iterator = typename Memory::const_iterator;
  using reverse_iterator = typename Memory::reverse_iterator;
  using const_reverse_iterator = typename Memory::const_reverse_iterator;

  InlinedVector() = default;
  explicit InlinedVector(std::size_t count, const T& value = T());
  InlinedVector(std::initializer_list<T> init);

  // Element access
  reference at(size_type pos) noexcept;
  const_reference at(size_type pos) const noexcept;
  reference operator[](size_type pos) noexcept;
  const_reference operator[](size_type pos) const noexcept;
  reference front() noexcept;
  const_reference front() const noexcept;
  reference back() noexcept;
  const_reference back() const noexcept;
  pointer data() noexcept;
  const_pointer data() const noexcept;

  // Iterators
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;
  reverse_iterator rbegin() noexcept;
  const_reverse_iterator crbegin() const noexcept;
  reverse_iterator rend() noexcept;
  const_reverse_iterator crend() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  constexpr size_type capacity() const noexcept;

  // Modifiers
  void clear() noexcept;
  iterator insert(const_iterator pos, const T& value);
  iterator insert(const_iterator pos, T&& value);
  iterator insert(const_iterator pos, size_type count, const T& value);
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  void push_back(const T& value);
  void push_back(T&& value);
  template <class... Args>
  reference emplace_back(Args&&... args);
  void pop_back();
  void resize(size_type count, const value_type& value = value_type{});

 private:
  Memory memory_{};
  size_type size_ = 0;
};

//////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
inline InlinedVector<T, N>::InlinedVector(std::size_t count, const T& value) {
  assert(count <= capacity() && "size must <= capacity");
  std::fill_n(memory_.begin(), count, value);
  size_ = count;
}

template <typename T, std::size_t N>
inline InlinedVector<T, N>::InlinedVector(std::initializer_list<T> init) {
  assert(init.size() <= capacity() && "size must <= capacity");
  std::copy(init.begin(), init.end(), memory_.begin());
  size_ = init.size();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reference InlinedVector<T, N>::at(
    size_type pos) noexcept {
  return const_cast<reference>(
      static_cast<const InlinedVector&>(*this).at(pos));
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reference InlinedVector<T, N>::at(
    size_type pos) const noexcept {
  if (pos < 0 || pos >= size()) {
    throw std::out_of_range{};
  }
  return (*this)[pos];
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reference InlinedVector<T, N>::operator[](
    size_type pos) noexcept {
  return const_cast<reference>(static_cast<const InlinedVector&>(*this)[pos]);
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reference
    InlinedVector<T, N>::operator[](size_type pos) const noexcept {
  return memory_[pos];
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reference
InlinedVector<T, N>::front() noexcept {
  return const_cast<reference>(
      static_cast<const InlinedVector&>(*this).front());
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reference
InlinedVector<T, N>::front() const noexcept {
  return memory_.front();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reference
InlinedVector<T, N>::back() noexcept {
  return const_cast<reference>(static_cast<const InlinedVector&>(*this).back());
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reference InlinedVector<T, N>::back()
    const noexcept {
  return memory_[size() - 1];
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::pointer
InlinedVector<T, N>::data() noexcept {
  return const_cast<pointer>(static_cast<const InlinedVector&>(*this).data());
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_pointer InlinedVector<T, N>::data()
    const noexcept {
  return memory_.data();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator
InlinedVector<T, N>::begin() noexcept {
  return memory_.begin();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_iterator
InlinedVector<T, N>::cbegin() const noexcept {
  return memory_.cbegin();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator
InlinedVector<T, N>::end() noexcept {
  return memory_.begin() + size();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_iterator InlinedVector<T, N>::cend()
    const noexcept {
  return memory_.cbegin() + size();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reverse_iterator
InlinedVector<T, N>::rbegin() noexcept {
  return memory_.rbegin() + capacity() - size();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reverse_iterator
InlinedVector<T, N>::crbegin() const noexcept {
  return memory_.crbegin() + capacity() - size();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::reverse_iterator
InlinedVector<T, N>::rend() noexcept {
  return memory_.rend();
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::const_reverse_iterator
InlinedVector<T, N>::crend() const noexcept {
  return memory_.crend();
}

template <typename T, std::size_t N>
inline bool InlinedVector<T, N>::empty() const noexcept {
  return size() == 0;
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::size_type InlinedVector<T, N>::size() const
    noexcept {
  return size_;
}

template <typename T, std::size_t N>
inline constexpr typename InlinedVector<T, N>::size_type
InlinedVector<T, N>::capacity() const noexcept {
  return N;
}

template <typename T, std::size_t N>
inline void InlinedVector<T, N>::clear() noexcept {
  size_ = 0;
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::insert(
    const_iterator pos, const T& value) {
  return emplace(pos, value);
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::insert(
    const_iterator pos, T&& value) {
  return emplace(pos, std::move(value));
}

namespace inlined_vector_internal {
template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator ToIterator(
    InlinedVector<T, N>& vec,
    typename InlinedVector<T, N>::const_iterator cit) {
  return vec.begin() + std::distance(vec.cbegin(), cit);
}
}  // namespace inlined_vector_internal

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::insert(
    const_iterator pos, size_type count, const T& value) {
  assert(size() + count <= capacity() && "size must <= capacity");
  std::fill_n(end(), count, value);
  std::rotate(pos, end(), end() + count);
  size_ += count;
  return inlined_vector_internal::ToIterator(*this, pos);
}

template <typename T, std::size_t N>
template <class InputIt>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::insert(
    const_iterator pos, InputIt first, InputIt last) {
  auto it = inlined_vector_internal::ToIterator(*this, pos);
  std::copy(first, last, end());
  std::size_t distance = std::distance(first, last);
  std::rotate(it, end(), end() + distance);
  size_ += distance;
  return it;
}

template <typename T, std::size_t N>
template <class... Args>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::emplace(
    const_iterator pos, Args&&... args) {
  assert(size() < capacity() && "size must <= capacity");
  *end() = T(std::forward<Args>(args)...);
  auto it = inlined_vector_internal::ToIterator(*this, pos);
  std::rotate(it, end(), end() + 1);
  ++size_;
  return it;
}

template <typename T, std::size_t N>
template <class... Args>
inline typename InlinedVector<T, N>::reference
InlinedVector<T, N>::emplace_back(Args&&... args) {
  return emplace(end(), std::forward<Args>(args)...);
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::erase(
    const_iterator pos) {
  return erase(pos, pos);
}

template <typename T, std::size_t N>
inline typename InlinedVector<T, N>::iterator InlinedVector<T, N>::erase(
    const_iterator first, const_iterator last) {
  auto first_it = inlined_vector_internal::ToIterator(*this, first);
  auto last_it = inlined_vector_internal::ToIterator(*this, last);
  std::rotate(first_it, last_it, end());
  size_ -= std::distance(first_it, last_it);
  return first_it;
}

template <typename T, std::size_t N>
inline void InlinedVector<T, N>::push_back(const T& value) {
  insert(end(), value);
}

template <typename T, std::size_t N>
inline void InlinedVector<T, N>::push_back(T&& value) {
  insert(end(), std::move(value));
}

template <typename T, std::size_t N>
inline void InlinedVector<T, N>::pop_back() {
  erase(end() - 1);
}

template <typename T, std::size_t N>
inline void InlinedVector<T, N>::resize(size_type count,
                                        const value_type& value) {
  if (count > size()) {
    insert(end(), count, value);
  } else if (count < size()) {
    erase(begin() + count, end());
  }
}

}  // namespace einu

#endif  // FIXED_SIZE_VECTOR_H_