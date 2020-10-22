#pragma once

#include <einu-core/entity_view.h>

#include "einu-window/window_comp.h"

namespace einu {
namespace window {
namespace sys {

void Init();

void Create(const ComponentBuffer<comp::Window>& buffer);



}  // namespace sys
}  // namespace window
}  // namespace einu