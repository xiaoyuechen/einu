#include "ecs-core/admin/World.h"
#include "ecs-core/system/I_system.h"

namespace ecs {

inline void World::update(time dt) {
  using namespace std;
  for_each(
      begin(sys_arr_), end(sys_arr_), [=](auto&& s) { s->update(dt); });
}
}  // namespace ecs