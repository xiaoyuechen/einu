#pragma once

#include <exception>
#include <string>

namespace einu {
namespace graphics {

class GLError final : public std::exception {
 public:
  GLError() = default;

  explicit GLError(const char* message) : message_{message} {}

  ~GLError() = default;

  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_{};
};

}  // namespace graphics
}  // namespace einu
