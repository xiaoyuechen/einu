#ifndef TYPE_MAPPING_H_
#define TYPE_MAPPING_H_

namespace ecs {

template <int v>
struct Int2Type;

template <typename T>
struct Type2Type;

//////////////////////////////////////////////////////////////////////////

template <int v>
struct Int2Type {
  static constexpr int value = v;
};

template <typename T>
struct Type2Type {
  using Type = T;
};

}  // namespace ecs

#endif  // TYPE_MAPPING_H_
