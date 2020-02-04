#include "ecs-engine/utility/file_reader.h"

#include <string>

namespace ecs {

FileReader::FileReader(const char* file_name, Mode mode) {
  auto file = std::ifstream(file_name, static_cast<int>(mode));
  if (!file) {
    throw std::runtime_error("could not open file: " + std::string(file_name));
  }
  file.seekg(0, file.end);
  size_t length = file.tellg();
  file.seekg(0, file.beg);
  content_.resize(length);
  file.read(content_.data(), length);
}

const std::vector<char>& FileReader::GetContent() const { return content_; }

FileWriter::FileWriter(const char* file_name, Mode mode) {
  ofstream_ = std::ofstream(file_name, static_cast<int>(mode));
  if (!ofstream_) {
    throw std::runtime_error("could not write file: " + std::string(file_name));
  }
}

void FileWriter::Write(const char* source, std::size_t count) {
  ofstream_.write(source, count);
}

void FileWriter::Close() { ofstream_.close(); }

}  // namespace ecs