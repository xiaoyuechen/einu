#pragma once

#include <fstream>
#include <vector>

namespace einu {

class FileReader {
 public:
  enum class Mode {
    TEXT = std::ios_base::in,
    BINARY = std::ios_base::binary,
  };

  FileReader(const char* file_name, Mode mode = Mode::TEXT);

  const std::vector<char>& GetContent() const;

 private:
  std::vector<char> content_{};
};

class FileWriter {
 public:
  enum class Mode {
    OVERWRITE = std::ios_base::out,
    APPEND = std::ios_base::app,
    BINARY = std::ios_base::binary,
  };

  FileWriter(const char* file_name, Mode mode = Mode::OVERWRITE);

  void Write(const char* source, std::size_t count);
  void Close();

 private:
  std::ofstream ofstream_;
};

}  // namespace einu

