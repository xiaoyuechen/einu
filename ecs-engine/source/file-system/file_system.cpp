#include "ecs-engine/file-system/file_system.h"

#include <fstream>
#include <stdexcept>

namespace ecs {

namespace file_system {

std::vector<char> ReadFileContent(const char* filename,
                                  std::ios_base::openmode mode) {
  auto file = std::ifstream(filename, mode);
  if (!file) {
    throw std::runtime_error("could not open file: " + std::string(filename));
  }
  file.seekg(0, file.end);
  size_t length = file.tellg();
  file.seekg(0, file.beg);
  auto content = std::vector<char>(length);
  file.read(content.data(), length);
  return content;
}

}  // namespace file_system

}  // namespace ecs