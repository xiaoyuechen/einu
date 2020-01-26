#pragma once
#include <set>
#include <typeindex>

namespace ecs {

class TypeMask {
 public:
  TypeMask() = default;
  explicit TypeMask(std::initializer_list<std::type_index> l);

  TypeMask& operator&=(const TypeMask& rhs);
  TypeMask& operator|=(const TypeMask& rhs);

  void Insert(const std::type_index& type_index);
  void Remove(const std::type_index& type_index);

  bool HasType(const std::type_index& type_index) const;

  std::set<std::type_index>::const_iterator cbegin() const;
  std::set<std::type_index>::const_iterator cend() const;
  std::set<std::type_index>::iterator begin();
  std::set<std::type_index>::iterator end();

 private:
  using Mask = std::set<std::type_index>;
  Mask mask_;

 private:
  TypeMask(const Mask& mask);

 private:
  friend bool operator==(const TypeMask& lhs, const TypeMask& rhs) noexcept;
  friend bool operator!=(const TypeMask& lhs, const TypeMask& rhs) noexcept;
  friend TypeMask operator&(const TypeMask& lhs, const TypeMask& rhs);
  friend TypeMask operator|(const TypeMask& lhs, const TypeMask& rhs);
};

bool operator==(const TypeMask& lhs, const TypeMask& rhs) noexcept;
bool operator!=(const TypeMask& lhs, const TypeMask& rhs) noexcept;
TypeMask operator&(const TypeMask& lhs, const TypeMask& rhs);
TypeMask operator|(const TypeMask& lhs, const TypeMask& rhs);

}  // namespace ecs
