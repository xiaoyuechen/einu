#pragma once
#include <typeindex>
#include <unordered_map>
#include "ecs-core/utilities/util.h"

namespace ecs {
class Component_type {
 public:
  template <typename T>
  Component_type();

 private:
  size_t id;

 private:
  friend std::less<Component_type>;
};

namespace {
static size_t type_counter = 0;
static std::unordered_map<std::type_index, size_t> type_id_map{};
}  // namespace

template <typename T>
inline Component_type::Component_type()
{
  auto type_index = util::get_type_index<T>();
  if (type_id_map.find(type_index) == std::end(type_id_map)) {
    type_id_map[type_index] = type_counter++;
  }
  id = type_id_map[type_index];
}
}  // namespace ecs

namespace std {
template <>
struct less<ecs::Component_type> {
  bool operator()(const ecs::Component_type& lhs,
                  const ecs::Component_type& rhs) const
  {
    return lhs.id < rhs.id;
  }
};
}  // namespace std