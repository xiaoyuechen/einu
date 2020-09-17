#pragma once

#include <ecs-tmp/type_list.h>

namespace ecs {

  class IComponent {};

  template<typename ... Components>
  using ComponentList = tmp::SubtypeList<IComponent, Components...>;

  class IWorld {};


}