#pragma once
#include <ios>
#include <vector>

namespace ecs {

namespace file_system {
std::vector<char> ReadFileContent(
    const char* filename, std::ios_base::openmode mode = std::ios_base::in);
}

}  // namespace ecs