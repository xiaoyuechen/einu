#pragma once

#include "einu-window/window_comp.h"

namespace einu {
namespace window {
namespace sys {

void Init();

void Terminate();

void Create(comp::Window& win);

void Destroy(comp::Window& win);

void MakeContextCurrent(comp::Window& win);

void PoolEvents(comp::Window& win);

void SwapBuffer(comp::Window& win);

using GLLoaderProc = void (*)();
GLLoaderProc GetProcAddress(const char* procname);

}  // namespace sys
}  // namespace window
}  // namespace einu