#pragma once

namespace ecs {

namespace detail {

template <typename Itr>
bool Equal(Itr lhs, Itr lhs_end, Itr rhs, Itr rhs_end) {
  if (lhs == lhs_end && rhs == rhs_end) {
    return true;
  } else if (lhs != lhs_end && rhs != rhs_end) {
    return *lhs == *rhs;
  }
  return false;
}

}  // namespace detail

template <typename Filter, typename Subject>
class FilterIterator {
 public:
  FilterIterator(Filter filter, Filter filter_end, Filter filtered,
                 Filter filtered_end, Subject subject)
      : filter_(filter)
      , filter_end_(filter_end)
      , filtered_(filtered)
      , filtered_end_(filtered_end)
      , subject_(subject) {
    MatchFilter();
  }

  FilterIterator& operator++() {
    ++filter_;
    MatchFilter();
    return *this;
  }

  FilterIterator operator++(int) {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  bool operator==(FilterIterator other) const {
    return detail::Equal(filter_, filter_end_, other.filter_,
                         other.filter_end_) ||
           detail::Equal(filtered_, filtered_end_, other.filtered_,
                         other.filtered_end_);
  }

  bool operator!=(FilterIterator other) const { return !(*this == other); }

  auto operator*() { return *subject_; }

 private:
  void MatchFilter() {
    if (filter_ != filter_end_) {
      while (filtered_ != filtered_end_ && *filtered_ != *filter_) {
        ++filtered_;
        ++subject_;
      }
    }
  }

  Filter filter_, filter_end_;
  Filter filtered_, filtered_end_;
  Subject subject_;
};  // namespace ecs

template <typename FilterContainer, typename SubjectContainer>
class Filter {
 public:
  Filter(const FilterContainer& filter, const FilterContainer& filtered,
         SubjectContainer& subject)
      : filter_(filter)
      , filtered_(filtered)
      , subject_(subject) {}

  auto begin() const {
    return FilterIterator(filter_.begin(), filter_.end(), filtered_.begin(),
                          filtered_.end(), subject_.begin());
  }
  auto begin() {
    return FilterIterator(filter_.begin(), filter_.end(), filtered_.begin(),
                          filtered_.end(), subject_.begin());
  }

  auto end() const {
    return FilterIterator(filter_.end(), filter_.end(), filtered_.end(),
                          filtered_.end(), subject_.end());
  }
  auto end() {
    return FilterIterator(filter_.end(), filter_.end(), filtered_.end(),
                          filtered_.end(), subject_.end());
  }

 private:
  const FilterContainer& filter_;
  const FilterContainer& filtered_;
  SubjectContainer& subject_;
};

template <typename FilterContainer, typename SubjectContainer>
class CopyFilter {
 public:
  using Filter = Filter<FilterContainer, SubjectContainer>;
  CopyFilter(const FilterContainer& filter, const FilterContainer& filtered,
             const SubjectContainer& subject)
      : subject_(subject)
      , filter_impl_(filter, filtered, subject_) {}

  auto begin() const { return filter_impl_.begin(); }
  auto begin() { return filter_impl_.begin(); }

  auto end() const { return filter_impl_.end(); }
  auto end() { return filter_impl_.end(); }

 private:
  SubjectContainer subject_;
  Filter filter_impl_;
};

}  // namespace ecs