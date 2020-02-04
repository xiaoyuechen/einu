#include "ecs-engine/graphics/texture.h"

#include <stdexcept>

#include "ecs-engine/graphics/stb_image.h"
#include "ecs-engine/utility/file_reader.h"

namespace ecs {

Texture::Texture() { glGenTextures(1, &texture_); }

Texture::~Texture() { glDeleteTextures(1, &texture_); }

namespace {

class Image {
  uint8_t* image_ = nullptr;
  int width_ = 0, height_ = 0, components_ = 0;

 public:
  explicit Image(const char* filename);
  ~Image();

  int Width() const { return width_; }
  int Height() const { return height_; }
  int Components() const { return components_; }
  uint8_t* Data() const { return image_; }
};

Image::Image(const char* filename) {
  auto file_reader = FileReader(filename, FileReader::Mode::BINARY);
  const auto& content = file_reader.GetContent();
  const auto data = reinterpret_cast<const uint8_t*>(content.data());
  auto size = static_cast<int>(content.size());
  image_ = stbi_load_from_memory(
      data, size, &width_, &height_, &components_, STBI_rgb_alpha);
  if (!image_) {
    throw std::runtime_error("could not read image: " + std::string(filename));
  }
}

Image::~Image() { stbi_image_free(image_); }
}  // namespace

void Texture::LoadFromFile(const char* filename) {
  auto bitmap = Image(filename);

  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               bitmap.Width(),
               bitmap.Height(),
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               bitmap.Data());
}

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, texture_); }

GLuint Texture::Get() const { return texture_; }

}  // namespace ecs