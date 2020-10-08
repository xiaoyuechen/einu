#pragma once

#include <einu-tmp/type_list.h>

#include "einu-core/i_singlenent.h"

namespace einu {

template <typename... Singlenents>
using SinglenentList = tmp::TypeList<Singlenents...>;

}