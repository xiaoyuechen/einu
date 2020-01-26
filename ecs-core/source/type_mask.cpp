#include "ecs-core/type_mask.h"

#include <algorithm>
#include <iterator>

namespace ecs {

TypeMask::TypeMask(std::initializer_list<std::type_index> l)
    : mask_(l) {}

TypeMask::TypeMask(const Mask& mask)
    : mask_(mask) {}

TypeMask& TypeMask::operator&=(const TypeMask& rhs) {
  *this = *this & rhs;
  return *this;
}

TypeMask& TypeMask::operator|=(const TypeMask& rhs) {
  *this = *this | rhs;
  return *this;
}

void TypeMask::Insert(const std::type_index& type_index) {
  mask_.insert(type_index);
}

void TypeMask::Remove(const std::type_index& type_index) {
  mask_.erase(type_index);
}

bool TypeMask::HasType(const std::type_index& type_index) const {
  return mask_.find(type_index) != mask_.end();
}

std::set<std::type_index>::const_iterator TypeMask::cbegin() const {
  return mask_.cbegin();
}

std::set<std::type_index>::const_iterator TypeMask::cend() const {
  return mask_.cend();
}

std::set<std::type_index>::iterator TypeMask::begin() { return mask_.begin(); }

std::set<std::type_index>::iterator TypeMask::end() { return mask_.end(); }

bool operator==(const TypeMask& lhs, const TypeMask& rhs) noexcept {
  return lhs.mask_ == rhs.mask_;
}

bool operator!=(const TypeMask& lhs, const TypeMask& rhs) noexcept {
  return !(lhs == rhs);
}

TypeMask operator&(const TypeMask& lhs, const TypeMask& rhs) {
  auto result = TypeMask::Mask{};
  std::set_intersection(std::begin(lhs.mask_),
                        std::end(lhs.mask_),
                        std::begin(rhs.mask_),
                        std::end(rhs.mask_),
                        std::inserter(result, std::begin(result)));
  return TypeMask(result);
}

TypeMask operator|(const TypeMask& lhs, const TypeMask& rhs) {
  auto result = TypeMask::Mask{};
  std::set_union(std::begin(lhs.mask_),
                 std::end(lhs.mask_),
                 std::begin(rhs.mask_),
                 std::end(rhs.mask_),
                 std::inserter(result, std::begin(result)));
  return TypeMask(result);
}

}  // namespace ecs