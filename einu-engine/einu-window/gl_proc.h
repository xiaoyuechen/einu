#pragma once

namespace einu {
namespace window {

using GLLoaderProc = void (*)();

GLLoaderProc GetProcAddress(const char* procname);

}  // namespace window
}  // namespace einu